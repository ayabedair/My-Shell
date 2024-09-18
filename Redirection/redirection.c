#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "redirection.h"

void handleRedirection(char *inFile, char *outFile, char *errFile, int append, int inRedirect, int outRedirect, int errRedirect) {
    int fd;

    // Handle input redirection
    if (inRedirect && inFile != NULL) {
        fd = open(inFile, O_RDONLY);
        if (fd < 0) {
            perror("Failed to open input file");
            exit(1);
        }
        // Redirect stdin to the input file
        if (dup2(fd, STDIN_FILENO) < 0) {
            perror("Failed to redirect stdin");
            exit(1);
        }
        close(fd);
    }

    // Handle output redirection
    if (outRedirect && outFile != NULL) {
        // Check if it is in append mode
        if (append) {
            fd = open(outFile, O_WRONLY | O_APPEND | O_CREAT, 0644);
        } else {
            fd = open(outFile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        }
        if (fd < 0) {
            perror("Failed to open output file");
            exit(1);
        }
        // Redirect stdout to the output file
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("Failed to redirect stdout");
            exit(1);
        }
        close(fd); 
    }

    // Handle error redirection
    if (errRedirect && errFile != NULL) {
        // Check if it is in append mode
        if (append) {
            fd = open(errFile, O_WRONLY | O_APPEND | O_CREAT, 0644);
        } else {
            fd = open(errFile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        }
        if (fd < 0) {
            perror("Failed to open error file");
            exit(1);
        }
        // Redirect stderr to the error file
        if (dup2(fd, STDERR_FILENO) < 0) {
            perror("Failed to redirect stderr");
            exit(1);
        }
        close(fd);
    }
}

