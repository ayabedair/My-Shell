#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mycd.h"

void runMycd (int argc, char **argv) {
	
	if (argc != 2) {
		perror("Usage: mycd <directory>");
		exit(EXIT_FAILURE);
	}

	if (chdir(argv[1]) != 0) {
		perror("Wrong path");
		exit(EXIT_FAILURE);
	}
}
