#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    pid_t id = fork();

    if (pid == 0) {
		printf("Hijo: soy %d\n", getpid());
		exit(1);
	} else {
		printf("Padre: soy %d\n", getpid());
		pause();
	}
	exit(0);
}