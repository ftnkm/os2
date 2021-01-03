#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

/* Prikazuje sadrzaj home page-a sa server soketa. Vraca indikator uspeha. */
void get_home_page(int socket_fd) {
    char buffer[10000];
    ssize_t number_characters_read;

    // Salje HTTP GET komandu za home page
    sprintf(buffer, "GET /\n");
    write(socket_fd, buffer, strlen(buffer));
    
    /* Cita sa soketa. Poziv za citanje mozda ne moze vratiti sve podatke
        u jednom trenutku, tako da nastavlja da pokusava dok ga ne prekinemo. */
    while (1) {
        number_characters_read = read(socket_fd, buffer, 10000);
        if (number_characters_read == 0)
            return;
        // Ispisuje podatke na standardni izlaz
        fwrite(buffer, sizeof(char), number_characters_read, stdout);
    }
}

int main(int argc, char *const argv[]) {
    int socket_fd;
    struct sockaddr_in name;
    struct hostent *hostinfo;

    // Kreira soket.
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);

    // Cuva ime servera u adresu soketa.
    name.sin_family = AF_INET;

    // Konvertuje iz stringa u brojeve.
    hostinfo = gethostbyname(argv[1]);
    if (hostinfo == NULL)
        return 1;
    else
        name.sin_addr = *((struct in_addr *)hostinfo -> h_addr);
    
    // Web serveri koriste port 80.
    name.sin_port = htons(80);
    
    // Konektuje se na Web server
    if (connect(socket_fd, (struct sockaddr *)&name, sizeof(struct sockaddr_in)) == -1) {
        perror("connect");
        return 1;
    }
    
    // Trazi server home page (pocetnu stranu)
    get_home_page(socket_fd);
    
    return 0;
}
