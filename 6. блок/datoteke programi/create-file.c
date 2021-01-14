#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[]){
    // Putanja gde ce se kreirati nova datoteka
    char* putanja = argv[1];

    // Dozvole za novu datoteku
    mode_t opcije = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

    // Kreira se datoteka
    int fd = open(putanja, O_WRONLY | O_EXCL | O_CREAT, opcije);
    
    if(fd == -1){
        // Dolazi do greske i ispisuje se poruka
        perror("open");
        return 1;
    }

    return 0;
}