#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    struct iovec *vec;
    struct iovec *vec_sledeci;

    /*
    Trebace nam "bafer" koji sadrzi karaktere za novi red.
    Koristite uobicajene char promenljive za to.
    */
    char novalinija = '\n';
    // Prvi argument u komandnoj liniji je ime datoteke
    char *imedatoteke = argv[1];

    /*
    Preskacemo prva dva elementa sa liste argumenata.
    Element 0 je ime programa, a element 1 je ime datoteke.
   */
    argc -= 2;
    argv += 2;
    
    /*
    Dodeljivanje niza elemenata iovec. Za to nam trebaju
    po dva za svaki element liste argumenata, jedan za sam
    tekst, a drugi za novi red.
    */
    vec = (struct iovec*) malloc(2 * argc * sizeof(struct iovec));

    // Petlja preko liste argumenata, pravljenje iovec upisa
    vec_sledeci = vec;
    for(int i = 0; i < argc; ++i){
        // Prvi element je tekst samog argumenta
        vec_sledeci->iov_base = argv[i];
        vec_sledeci->iov_len = strlen(argv[i]);
        ++vec_sledeci;
        /*
        Drugi red je samo karakter za novi red. U redu je ako
        visestruki elementi iz niza struktura iovec pokazuju na
        isti deo memorije.
        */
       vec_sledeci->iov_base = &novalinija;
       vec_sledeci->iov_len = 1;
       ++vec_sledeci;
    }

    // Upisivanje argumenta u datoteku
    fd = open(imedatoteke, O_WRONLY | O_CREAT);
    writev(fd, vec, 2 * argc);
    close(fd);
    free(vec);

    return 0;
}