#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*  Upisuje "count" broj puta poruku u tok "stream", 
    izmedju upisivanja pravi pauzu jednu sekundu. */
void writer(const char *message, int count, FILE *stream) {
    for ( ; count > 0; --count) {
        // Upisuje poruku u niz, i odmah ih salje dalje...
        fprintf(stream, "%s\n", message);
        fflush(stream);
        sleep(1); // Ceka jednu sekundu
    }
}

// Cita proizvoljne stringove iz niza sto je duze moguce
void reader(FILE *stream) {
    char buffer[1024];
    /* Cita sve dok ne stigne do kraja niza. fgets cita do nove linije ili do kraja. */
    while (!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL)
        fputs(buffer, stdout);
}

int main() {
    int fds[2];
    pid_t pid;
    // Kreira pipe. Fajl deskriptori oba kraja se smestaju u fds
    pipe(fds);

    // Stvara se proces dete
    pid = fork();
    if (pid == (pid_t)0) {
        FILE *stream;
        /* Ovo je proces dete. Zatvara kopiju kraja za upis fajl deskriptora - nepotrebna je. */
        close(fds[1]);
        /* Konvertuje file-deskriptor za citanje u objekat tipa FILE i cita iz njega. */
        stream = fdopen(fds[0], "r");
        reader(stream);
        close(fds[0]);
    } else {
        // Ovo je proces roditelj
        FILE *stream;
        // Zatvara nasu kopiju kraja za citanje datoteka 
        close(fds[0]);
        /* Konvertuje file-descriptor upisa u datoteka object i upisuje u njega */
        stream = fdopen(fds[1], "w");
        writer("Zdravo, svete!", 5, stream);
        close(fds[1]);
    }
    return 0;
}
