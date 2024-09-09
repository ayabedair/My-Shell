#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "myrm.h"

void runMyrm(int argc, char **argv) {

    int force = 0;

    if (argc == 1) {
    	perror("Usage: myrm <file1> [file2 ...]");
	exit(EXIT_FAILURE);
    }

    // Check force command-line
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '\0') {
            force = 1;
        }
    }

    // Remove files
    for (int i = 1; i < argc; i++) {
      	// Skip force command-line
        if (argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '\0') {
            continue;
        }

        if (unlink(argv[i]) != 0) {
            if (errno == ENOENT) {
                // File does not exist
                printf("Error: %s: No such file\n", argv[i]);
            } else if (errno == EACCES) {
                // Permission denied
                printf("Error: %s: Permission denied\n", argv[i]);
            } else {
                // Other errors
                perror("Faild to remove file(s)");
            }

            if (!force) {
                exit(EXIT_FAILURE);
            }
        }
    }
}

