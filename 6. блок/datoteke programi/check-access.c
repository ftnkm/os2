#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *putanja = argv[1];
    int pov_vred;

    // Provera da li datoteka postoji
    pov_vred = access(putanja, F_OK);
    if(pov_vred == 0)
        printf("%s postoji\n", putanja);
    else {
        if(errno == ENOENT) 
            printf("%s ne postoji\n", putanja);
        else if(errno == EACCES)
            printf("Ne moze se pristupiti %s\n", putanja);
        return 0;
    }

    // Proverava se dozvola citanja - read
    pov_vred = access(putanja, R_OK);
    if(pov_vred == 0)
        printf("%s moze da se cita\n", putanja);
    else
        printf("%s ne moze da se cita\n", putanja);

    // Proverava se dozvola upisivanja - write
    pov_vred = access(putanja, W_OK);
    if(pov_vred == 0)
        printf("U %s moze da se upisuje\n", putanja);
    else if(errno == EACCES) 
        printf("U %s ne moze da se upisuje (nema W dozvole)\n", putanja);
    else if(errno == EROFS)
        printf("U %s ne moze da se upisuje - read only FS\n", putanja);
    
    return 0;
}