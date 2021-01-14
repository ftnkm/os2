#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){

char* filename = "sfjd";
char* vector = "sfjd";
int vector_length = 5;


FILE* stream = fopen (filename, "w");
int file_descriptor = fileno (stream);
writev (file_descriptor, vector, vector_length);

close (file_descriptor);

umask (S_IRWXO | S_IWGRP); 


}