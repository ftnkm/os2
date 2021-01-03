#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

void error(char *poruka) {
    perror(poruka);
    exit(0);
}

int main(int argc, char *argv[]) {
    int fd_soketa, br_porta, n;
    struct sockaddr_in adr_servera;
    struct hostent *server;
    char bafer[256];

    if (argc < 3) {
        fprintf(stderr, "ispravan poziv: %s ime_hosta port\n", argv[0]);
        exit(0);
    }

    br_porta = atoi(argv[2]);
    fd_soketa = socket(AF_INET, SOCK_STREAM, 0);

    if (fd_soketa < 0)
        error("GRESKA prilikom otvaranja soketa");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "GRESKA, ne postoji taj host\n");
        exit(0);
    }

    bzero((char *) &adr_servera, sizeof(adr_servera));
     
    adr_servera.sin_family = AF_INET;

    bcopy((char *)server->h_addr,
          (char *)&adr_servera.sin_addr.s_addr,
          server->h_length);

    adr_servera.sin_port = htons(br_porta);

    if (connect(fd_soketa, (struct sockaddr *)&adr_servera, sizeof(adr_servera)) < 0)
        error("GRESKA prilikom povezivanja");

    printf("Molimo Vas, unesite poruku: ");
    bzero(bafer, 256);
    fgets(bafer, 255, stdin);
    n = write(fd_soketa, bafer, strlen(bafer));

    if (n < 0)
        error("GRESKA prilikom upisivanja u soket");

    bzero(bafer, 256);
    n = read(fd_soketa, bafer, 255);

    if (n < 0)
        error("GRESKA prilikom citanja iz soketa");

    printf("%s\n", bafer);
    return 0;
}