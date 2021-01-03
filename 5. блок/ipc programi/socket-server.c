#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/* Cita poruke sa soketa i prikazuje ih. To radi sve do zatvaranja soketa.
   Vraca nenultu vrednost ako klijent posalje "quit", a nulu u drugom slucaju. */
int server(int client_socket) {
    while(1) {
        int length;
        char *text;

        /* Prvo cita duzinu tekstualne poruke sa soketa.
    	   Ako citanje vrati nulu, klijent zatvara konekciju. */
        if (read(client_socket, &length, sizeof(length)) == 0)
            return 0;

        // Alocira se bafer da bi prihvatio poruku.
        text = (char *) malloc(length);

        // Cita sam tekst i prikazuje ga
        read(client_socket, text, length);
        printf("%s\n", text);

        // Oslobadja bafer
        free(text);

        // Ako klijent posalje poruku "quit," sve je zavrseno
        if (!strcmp(text, "quit"))
            return 1;
    }
}

int main(int argc, char *const argv[]) {
    const char *const socket_name = argv[1];
    int socket_fd;
    struct sockaddr_un name;
    int client_sent_quit_message;

    // Kreira soket
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

    // Ukazuje na to da je ovo server
    name.sun_family = AF_LOCAL;

    strcpy(name.sun_path, socket_name);
    bind(socket_fd, (struct sockaddr *)&name, SUN_LEN(&name));

    // Ceka - osluskuje konekcije
    listen(socket_fd, 5);

    /* Ponavlja prihvatanje konekcija, cineci da jedan server radi sa svakim
       klijentom. Nastavlja dok klijent ne posalje "quit" poruku. */

    do {
        printf("Ulazi u while\n");
        struct sockaddr_un client_name;
        socklen_t client_name_len;
        int client_socket_fd;

        // Prihvata konekciju
        client_socket_fd = accept(socket_fd, (struct sockaddr *)&client_name, &client_name_len);

        // Rukuje konekcijom
        client_sent_quit_message = server(client_socket_fd);

        // Zatvara nas kraj konekcije
        close(client_socket_fd);
    } while (!client_sent_quit_message);


    // Uklanja soket datoteka
    close(socket_fd);
    unlink(socket_name);

    return 0;
}
