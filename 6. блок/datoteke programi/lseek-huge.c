#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int nula = 0;
    const int megabajt = 1024 * 1024;
    
    char* imedatoteke = argv[1];
    size_t duzina = (size_t) (atoi(argv[2]) * megabajt);

    // Otvaranje nove datoteke
    int fd = open(imedatoteke, O_WRONLY | O_CREAT | O_APPEND, 0666);

    // Prelazimo na bajt manje od mesta gde hocemo da bude kraj
    lseek(fd, duzina - 1, SEEK_SET);

    // Upisujemo jedinstven nula-bajt
    write(fd, &nula, 1);

    // Zavrseno
    close(fd);

    return 0;
}