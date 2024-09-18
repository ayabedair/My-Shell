#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "mygrep.h"

#define MAX_LINE_LENGTH  1024
void runMygrep(int argc, char **argv) {
	//Check number of arguments
	if (argc < 2) {
		perror("Usage: mygrep <word> <file1> [file2 ...]");
		exit(EXIT_FAILURE);
	}

	for (int i = 2; i < argc; i++) {
        	FILE *file = fopen(argv[i], "r");
        	if (file == NULL) {
            		perror(argv[i]);
            		exit(EXIT_FAILURE);
        	}

        	char line[MAX_LINE_LENGTH];
    		while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        		if (strstr(line, argv[1]) != NULL) {
            			printf("%s: %s",argv[i], line);
				if (i > argc - 1)
					printf("\n");
        		}
    		}	

        	fclose(file);
        }


}
