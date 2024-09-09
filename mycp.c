#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "mycp.h"

#define BUF_SIZE  100

void runMycp (int argc, char **argv){

	int source_fd, dest_fd, data;
	char buf[BUF_SIZE];
	struct stat statbuf;

	//check number of arguments
	if (argc != 3) {
		perror("Usage: mycp source_file distenation_file");
		exit(EXIT_FAILURE);
	}

	//open source file
	source_fd = open(argv[1], O_RDONLY);
	if (source_fd == -1) {
		perror("Unable to open source file");
		exit(EXIT_FAILURE);
	}

	//Check source file status
	if (fstat(source_fd, &statbuf) == -1) {
		perror("Error in source file status");
		close(source_fd);
		exit(EXIT_FAILURE);
	}


	//Open destination file
	dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, statbuf.st_mode);
	if (dest_fd == -1) {
		perror("Unable to open destination file");
		close(source_fd);
		exit(EXIT_FAILURE);
	}

	//Copy from source to destination
	while ((data = read(source_fd, buf, BUF_SIZE)) > 0) {
		write(dest_fd, buf, data);
	}

	close(source_fd);
	close(dest_fd);
}
