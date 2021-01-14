#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char* datoteka = argv[1];
    int fd;
    struct flock lock;

    printf("Otvaranje datoteke %s\n", datoteka);
    // Otvaranje deskriptora datoteke
    fd = open(datoteka, O_WRONLY);

    printf("Zakljucavanje\n");
    // Inicijalizacija flock strukture
    memset(&lock, 0, sizeof(lock));

    lock.l_type = F_WRLCK;
    // Postavljanje zabrane pisanja (write lock) na datoteku
    fcntl(fd, F_SETLKW, &lock);

    printf("Zakljucano! Pritisni <Enter> za otkljucavanje...\n");

    // Cekamo na <Enter>, ali u sustini ne proveravamo, moze bilo koje dugme
    getchar();
    printf("Otkljucavanje!\n");

    // Otkljucavanje
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    close(fd);
    
    return 0;
}