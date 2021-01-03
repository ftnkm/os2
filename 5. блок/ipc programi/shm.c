#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    int segment_id;
    char *shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;

    // Alociranje deljivog memorijskog segmenta - SHMGET
    segment_id = shmget(IPC_PRIVATE, shared_segment_size,
                        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    
    // Pridruzivanje deljivog memorijskog segmenta - SHMAT
    shared_memory = (char *) shmat(segment_id, 0, 0);
    printf("Deljiva memorija pridruzena na adresi %p\n", shared_memory);
    
    // Odredjivanje velicine segmenta - SHMCTL
    shmctl(segment_id, IPC_STAT, &shmbuffer);
    segment_size = shmbuffer.shm_segsz;
    printf("Velicina segmenta: %d\n", segment_size);
    
    // Upisivanje stringa u deljivi memorijski segment
    sprintf(shared_memory, "Zdravo svete!");
    printf("Upisan string u deljivu memoriju!\n");
    
    // Odbacivanje deljivog memorijskog segmenta - SHMDT
    shmdt(shared_memory);
    
    // Ponovno pridruzivanje deljivog segmenta na drugoj adresi
    shared_memory = (char *) shmat(segment_id, (void *)0x5000000, 0);
    printf("Deljiva memorija ponovo pridruzena na adresi %p\n", shared_memory);
    
    // Ispisivanje stringa iz deljive memorije
    printf("Procitan string iz deljive memorije:\n\t %s \n", shared_memory);
    
    // Odbacivanje deljivog memorijskog segmenta - SHMDT
    //shmdt(shared_memory);
    
    // Oslobadjanje (dealokacija) deljivog memorijskog segmenta - SHMCTL
    // shmctl(segment_id, IPC_RMID, 0);
    return 0;
}