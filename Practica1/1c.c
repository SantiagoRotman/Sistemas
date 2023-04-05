#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int rc;
	int  d;
	
	d = dup(1);
	close(1);
	rc = write(d, "asdasd\n", 7);
	

	fprintf(stderr, "rc=%i\n", rc);
	exit(0);
}