#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
	/* last argument is M and all before it are part of the set */
	int size = argc - 2;
	int *in = malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i) {
		in[i] = atoi(argv[i + 1]);
	}
	int M = atoi(argv[argc - 1]);

	return 0;
}
