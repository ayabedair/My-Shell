#include <stdio.h>
#include <string.h>
#include "myecho.h"

void runMyecho (int argc, char **argv) {
	
	int new_line = 1;

	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		new_line = 0;
		argv++;
		argc--;
	}

	for (int i = 1; i < argc; i++) {
		printf("%s", argv[i]);

		if(i != argc - 1)
			printf(" ");
	}

	if (new_line)
		printf("\n");
}
