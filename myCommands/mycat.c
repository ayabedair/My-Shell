#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "mycat.h"

#define BUF_SIZE  1024
void runMycat (int argc, char **argv) {

	//Check number of arguments
	if (argc < 2) {
		perror("Usage: mycat <file1> [file2 ...]");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i < argc; i++) {
        	int fd = open(argv[i], O_RDONLY);
        	if (fd == -1) {
            		perror(argv[i]);
            		exit(EXIT_FAILURE);
        	}

        	// Read and print files contents
		char buf[BUF_SIZE];
        	int bytesRead;

		while ((bytesRead = read(fd, buf, sizeof(buf))) > 0) {
            		if (write(STDOUT_FILENO, buf, bytesRead) == -1) {
                		perror("Failed to write files contents");
                		close(fd);
                		exit(EXIT_FAILURE);
            		}
        	}	

        	if (bytesRead == -1) {
            		perror("Failed to read files contents");
        	}

        	close(fd);
        }

}
