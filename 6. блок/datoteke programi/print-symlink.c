#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char ciljna_putanja[256];
    char* sim_putanja = argv[1];

    // Pokusaj da se procita ono na sta ukazuje sim. veza
    int len = readlink(sim_putanja, ciljna_putanja, sizeof(ciljna_putanja));

    if(len == -1){
        // Neuspesan poziv
        if(errno = EINVAL)
            // Ovo nije simbolicka veza
            fprintf(stderr, "%s nije simbolicka veza\n", sim_putanja);
        else {
            // Neki drugi problem, ispisujemo genericku poruku
            perror("readlink");
            return 1;
        }
    } else {
        // Niz ciljna_putanja se mora zavrsiti NULL karakterom
        ciljna_putanja[len] = '\0';
        // Ispisujemo putanju do ciljne datoteke
        printf("%s\n", ciljna_putanja);
    }
    return 0;
}