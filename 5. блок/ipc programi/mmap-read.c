#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

int main(int argc, char* const argv[]) {
    int fd;
    void* file_memory;
    int integer;

    // Otvaranje datoteke
    fd =  open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);

    // Stvaranje mapirane datoteke
    file_memory = mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    // Citanje celobrojne vrednosti, stampanje i udvorostrucavanje
    sscanf(file_memory, "%d", &integer);
    printf("Vrednost: %d\n", integer);
    sprintf((char*) file_memory, "%d\n", 2*integer);

    // Oslobadjanje memorije (nepotrebno jer se program svakako nakon ovoga zavrsava)
    munmap(file_memory, FILE_LENGTH);

    return 0;
}
