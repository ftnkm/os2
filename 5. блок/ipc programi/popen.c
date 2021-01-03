#include <stdio.h>
#include <unistd.h>

int main () {
	FILE* stream = popen ("sort", "w"); 
	fprintf (stream, "Ovo je test.\n");
	fprintf (stream, "Zdravo, svete.\n");
	fprintf (stream, "Ovaj program nije dosadan!\n"); 
	fprintf (stream, "Necemo pauzu.\n");
	fprintf (stream, "Hocemo domaci!\n");
	
	return pclose(stream);
}
