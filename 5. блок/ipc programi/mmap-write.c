#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

// Vraca ujednacene slucajne brojeve u opsegu [low, high]
int random_range(unsigned const low, unsigned const high) {
    unsigned const range = high - low + 1;
    return low + (int)(((double)range) * rand() / (RAND_MAX + 1.0));
}

int main(int argc, char *const argv[]) {
    int fd;
    void *file_memory;

    // Generator slucajnih brojeva
    srand(time(NULL));

    // Priprema datoteku dovoljno veliku za prihvatanje neoznacenog celog broja
    // Ime datoteke se prosledjuje preko standardnog ulaza
    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek(fd, FILE_LENGTH + 1, SEEK_SET);
    write(fd, "", 1);
    lseek(fd, 0, SEEK_SET);

    // Kreira mapiranu memoriju
    file_memory = mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    // Upisuje slucajan ceo broj u mapirani memorijski prostor
    sprintf((char *)file_memory, "%d\n", random_range(-100, 100));

    // Oslobadja memoriju (nepotrebno jer se program svakako nakon ovoga zavrsava)
    munmap(file_memory, FILE_LENGTH);
    return 0;
}
