/* A C program to return an error message */

#include "die_with_error.h"

void die_with_error(char *msg) {
	fprintf(stderr, "%s : %s\n", msg, strerror(errno));
	exit(-1);
}
