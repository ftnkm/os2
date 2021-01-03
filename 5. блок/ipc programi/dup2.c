#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fds[2];
    pid_t pid;
    
    pipe(fds);    // Kreira se pipe
    pid = fork(); // Stvara se proces dete.

    if (pid == (pid_t) 0) { 
        // Ovo je proces dete.
        // Zatvara se nasa kopija kraja za upis file-deskriptora
        close(fds[1]);
        // Povezuje se kraj za citanje pipe na standardni ulaz
        dup2(fds[0], STDIN_FILENO);
        // Zamenjuje se proces dete programom za sortiranje
        execlp("sort", "sort", (char *) 0);
    } else { 
        // Ovo je proces roditelj.
        FILE *stream;
        // Zatvara se nasa kopija kraja za citanje file-deskriptora
        close(fds[0]);

        /* Kovertuje se file deskriptor za upis i vrsi se upisivanje u njega. */
        stream = fdopen(fds[1], "w");
        fprintf(stream, "Ovo je test.\n");
        fprintf(stream, "Zdravo, svete.\n");
        fprintf(stream, "Ovaj program nije dosadan!\n");
        fprintf(stream, "Necemo pauzu.\n");
        fprintf(stream, "Hocemo domaci!\n");
        
        fflush(stream);
        close(fds[1]);

        // Ceka se da proces dete zavrsi
        waitpid(pid, NULL, 0); 
    }
    return 0;
}
