#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int read_fd, write_fd;
    struct stat stat_baf;
    off_t ofset = 0;

    // Otvaranje ulazne datoteke
    read_fd = open(argv[1], O_RDONLY);

    // Dobijanje velicine ulazne datoteke
    fstat(read_fd, &stat_baf);

    /*
    Otvaranje izlazne datoteke za upis, i to sa istim dozvolama
    kao kod ulzane datoteke.
    */
    write_fd = open(argv[2], O_WRONLY | O_CREAT, stat_baf.st_mode);

    // Brzo kopiranje
    sendfile(write_fd, read_fd, &ofset, stat_baf.st_size);

    // Zatvaramo datoteku
    close(read_fd);
    close(write_fd);

    return 0;
}