#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// Vraca string koji predstavlja tekuci datum i vreme
char* get_timestamp(){
    time_t now = time(NULL);
    return asctime(localtime(&now));
}

int main(int argc, char *argv[]) {
    // Datoteka u koju treba da se doda vremenska oznaka     
    char* imedatoteke = argv[1];

    // Uzima tekucu vremensku oznaku
    char* timestamp = get_timestamp();

    // Otvara datoteku za upis. Ako postoji, pristupa joj.
    int fd = open(imedatoteke, O_WRONLY | O_CREAT | O_APPEND, 0666);

    // Racuna duzinu timestamp stringa
    size_t duzina = strlen(timestamp);

    // Upisuje timestamp u datoteku
    write(fd, timestamp, duzina);

    // Zavrseno
    close(fd);

    return 0;
}