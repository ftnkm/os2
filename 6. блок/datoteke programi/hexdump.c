#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    unsigned char bafer[16];
    size_t ofset = 0;
    size_t procitani_bajtovi;

    // Otvara se datoteka za citanje
    int fd = open(argv[1], O_RDONLY);

    /*
    Cita se iz datoteke, karakter po karakter. Postupak se nastavlja sve
    dok citanje ne postane "kratko" (tj. kada broj procitanih bajtova
    postane manji od trazenog), ovo ukazuje da se stiglo do kraja datoteke.
    */
    do {
        // Citanje bafera
        procitani_bajtovi = read(fd, bafer, sizeof(bafer));
        // Upisivanje pomeraja u datoteku, pracen samim bajtovima
        printf("0x%06x : ", ofset);
        for (int i = 0; i < procitani_bajtovi; ++i)
            printf("%02x ", bafer[i]);
        printf("\n");
        // Pamti nasu poziciju u datoteci
        ofset += procitani_bajtovi;
    } while (procitani_bajtovi == sizeof(bafer));
    
    // Zavrseno
    return 0;
}