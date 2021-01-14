#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Funkcija koja vraca tip datoteke
const char* daj_tip_datoteke(const char* putanja){
    struct stat st;
    lstat(putanja, &st);

    if (S_ISLNK(st.st_mode))
        return "simbolicka veza";
    else if (S_ISDIR(st.st_mode))
        return "direktorijum";
    else if (S_ISCHR(st.st_mode))
        return "karakter uredjaj";
    else if (S_ISBLK(st.st_mode))
        return "blok uredjaj";
    else if (S_ISFIFO(st.st_mode))
        return "fifo";
    else if (S_ISSOCK(st.st_mode))
        return "soket";
    else if (S_ISREG(st.st_mode))
        return "regularna datoteka";
    else
        // Neocekivan rezultat, datoteka mora da bude jedno od gorenavedenog
        assert(0);
}

int main(int argc, char *argv[]) {
    char* dir_putanja;
    DIR* dir;
    struct dirent* stavka;
    char putanja_stavke[PATH_MAX + 1];
    size_t duz_putanje;

    if(argc >= 2)
        // Ako je direktorijum zadat kao argument, koristimo ga
        dir_putanja = argv[1];
    else
        // U suprotnom, koristimo trenutni direktorijum
        dir_putanja = ".";
    
    // Kopiramo putanju direktorijuma u putanja_stavke
    strncpy(putanja_stavke, dir_putanja, sizeof(putanja_stavke));
    duz_putanje = strlen(dir_putanja);

    // Ako se putanja direktorijuma ne zavrsava kosom crtom, ona se dodaje
    if(putanja_stavke[duz_putanje - 1] != '/'){
        putanja_stavke[duz_putanje] = '/';
        putanja_stavke[duz_putanje + 1] = '\0';
        ++duz_putanje;
    }

    // Pocetak operacije listanja direktorijuma
    dir = opendir(dir_putanja);
    while ((stavka = readdir(dir)) != NULL) {
        const char* tip;
        strncpy(putanja_stavke + duz_putanje, stavka->d_name,
                    sizeof(putanja_stavke) - duz_putanje);
        // Odredjivanje tipa datoteke (stavke u direktorijumu)
        tip = daj_tip_datoteke(putanja_stavke);
        // Ispisivanje tipa i punog imena sa putanjom
        printf("%-18s: %s\n", tip, putanja_stavke);
    }
    
    // Kraj programa
    closedir(dir);
    return 0;
}