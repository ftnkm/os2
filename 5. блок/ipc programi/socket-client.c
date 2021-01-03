#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

// Upisuje u soket tekst dat putem deskriptora SOCKET_FD
void write_text(int socket_fd, const char *text) {
    // Upisuje broj bajtova u string, ukljucujuci NULL zavrsetak
    int length = strlen(text) + 1;
    write(socket_fd, &length, sizeof(length));
    // Upisuje string
    write(socket_fd, text, length);
}

int main(int argc, char *const argv[]) {
    const char *const socket_name = argv[1];
    const char *const message = argv[2];
    int socket_fd;
    struct sockaddr_un name;

    // Kreira soket
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

    // Cuva ime servera u adresi soketa
    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, socket_name);
    
    // Konektuje soket
    connect(socket_fd, (struct sockaddr *) &name, SUN_LEN (&name));
    
    // Upisuje tekst sa komandne linije u soket
    write_text(socket_fd, message);
    
    close(socket_fd);
    return 0;
}
