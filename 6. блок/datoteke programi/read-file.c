#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
Funkcija ucitava sadrzaj datoteke (IMEDAT) u bafer. Velicna bafera
se cuva u *duzina. Funkcija vraca bafer koji korisnik treba da izprazni.
Ako makro ne odgovori da li je datoteka regularna - vraca se NULL.
*/

char *citaj_datoteku(const char *imedat) {
    int fd;
    struct stat file_info;
    char *bafer;
    size_t *duzina = malloc(sizeof(size_t));

    // Otvaramo datoteku
    fd = open(imedat, O_RDONLY);
    // Uzimamo informacije o njoj
    fstat(fd, &file_info);
    *duzina = file_info.st_size;

    // Obratite paznju da li je u pitanju regularna datoteka
    if (!S_ISREG(file_info.st_mode)) {
        // Nije regularna, odustajemo
        close(fd);
        return NULL;
    }

    // Dodeljujemo dovoljno veliki bafer za sadrzaj datoteke
    bafer = (char *)malloc(*duzina);

    // Ucitavamo datoteku u bafer
    read(fd, bafer, *duzina);

    // Zavrsavamo rad
    close(fd);
    return bafer;
}

int main(int argc, char *argv[]) {
    char *imedat = argv[1];
    char *bafer = citaj_datoteku(imedat);
    printf("Bafer je: \n%s\n", bafer);

    return 0;
}