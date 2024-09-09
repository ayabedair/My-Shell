#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "mycat.h"
#include "myecho.h"
#include "mymv.h"
#include "myrm.h"
#include "mycp.h"
#include "mypwd.h"
#include "mycd.h"
//#include "program.h"
#include <limits.h>

#define MAX_CMD_SIZE  1024
#define MAX_ARG_SIZE  150
#define BOLD_MAGENTA   "\x1b[35m\x1b[1m"
#define BOLD_YELLOW 	"\x1b[33m\x1b[1m"
#define COLOR_RESET 	"\x1b[0m"

// Parse the input command
void parseCommand(char *cmd, char **args) {
    char *token = strtok(cmd, " \n");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
}

// Count number of arguments in the args array
int countArgs(char **args) {
    int count = 0;
    while (args[count] != NULL) {
        count++;
    }
    return count;
}

// Function to print the shell prompt with username and current directory
void printPrompt() {
    // Get the username
    char *user = getlogin();
    if (user == NULL) {
        perror("getlogin error");
        exit(EXIT_FAILURE);
    }

    // Get the current working directory
    char cwd[PATH_MAX]; 
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd error");
        exit(EXIT_FAILURE);
    }

    // Print the prompt with colors:
    printf(BOLD_YELLOW "%s@" BOLD_MAGENTA "%s" COLOR_RESET "> ", user, cwd);
}

int main() {
    char cmd[MAX_CMD_SIZE];
    char *args[MAX_ARG_SIZE];
    int status;

    while (1) {
 	printPrompt();       

	if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            perror("fgets error");
            continue;  // Continue loop instead of exit on error
        }

        // Remove newline from input
        cmd[strcspn(cmd, "\n")] = '\0';

        // Parse the input command
        parseCommand(cmd, args);

        // Check if the input is empty
        if (args[0] == NULL) {
            continue;
        }

        // Count the number of arguments
        int argc = countArgs(args);

        pid_t pid = fork();
	if(pid < 0) {
		perror("fork error");
                exit(EXIT_FAILURE);	
	} else if (pid == 0) {
		if (strcmp(args[0], "mypwd") == 0) {
            		runMypwd();
        	} else if (strcmp(args[0], "mycd") == 0) {
            		runMycd(argc, args);
        	} else if (strcmp(args[0], "myecho") == 0) {
            		runMyecho(argc, args);
        	} else if (strcmp(args[0], "mycat") == 0) {
            		runMycat(argc, args);
        	} else if (strcmp(args[0], "myrm") == 0) {
            		runMyrm(argc, args);
        	} else if (strcmp(args[0], "mycp") == 0) {
            		runMycp(argc, args);
        	} else if (strcmp(args[0], "mymv") == 0) {
            		runMymv(argc, args);
        	} else {
			execvp(args[0], args);
	                printf("execvp error");
        	        exit(EXIT_FAILURE);
		}
	}else {
		wait(&status);
	}
    }
    return 0;
}

