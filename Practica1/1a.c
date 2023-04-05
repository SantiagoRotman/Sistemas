#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int rc;

	close(1);
	rc = write(1, "asdasd\n", 7);
	fprintf(stderr, "rc=%i\n", rc);
	exit(0);
}
