#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void ispisi_gresku(char *poruka) {
    perror(poruka);
    exit(1);
}

int main(int argc, char *argv[]) {
    int fd_soketa, fd_novog_soketa, br_porta, len_klijenta;
    char bafer[256];
    struct sockaddr_in adr_servera, adr_klijenta;
    int n;

    if (argc < 2) {
        fprintf(stderr, "GRESKA, niste uneli port\n");
        exit(1);
    }

    fd_soketa = socket(AF_INET, SOCK_STREAM, 0);

    if (fd_soketa < 0)
        ispisi_gresku("GRESKA prilikom otvaranja soketa");

    bzero((char *) &adr_servera, sizeof(adr_servera));

    br_porta = atoi(argv[1]);

    adr_servera.sin_family = AF_INET;
    adr_servera.sin_port = htons(br_porta);
    adr_servera.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd_soketa, (struct sockaddr *) &adr_servera,
             sizeof(adr_servera)) < 0)
        ispisi_gresku("GRESKA prilikom binding-a");

    
    char ip_servera[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &adr_servera.sin_addr, ip_servera, sizeof(ip_servera));
    
    printf("Pokrenut server %s na portu %d\n", ip_servera, br_porta);
    
    listen(fd_soketa, 5);
    len_klijenta = sizeof(adr_klijenta);
    fd_novog_soketa = accept(fd_soketa, (struct sockaddr *)&adr_klijenta, &len_klijenta);

    if (fd_novog_soketa < 0)
        ispisi_gresku("GRESKA prilikom accept-a");

    bzero(bafer, 256);
    n = read(fd_novog_soketa, bafer, 255);

    if (n < 0)
        ispisi_gresku("GRESKA prilikom citanja iz soketa");

    printf("Poruka: %s\n", bafer);
    n = write(fd_novog_soketa, "Poruka primljena", 18);

    if (n < 0)
        ispisi_gresku("GRESKA prilikom upisivanja u soket");

    return 0;
}