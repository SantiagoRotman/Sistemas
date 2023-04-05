#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int c;
    FILE *fd = fopen("caca.txt", "r");
	c = fgetc(fd);
    printf("%c\n",c);
    
    ungetc((int)'x', fd);
    fflush(fd);
    c = fgetc(fd);
    printf("%c\n",c);
    
    fclose(fd);
}
