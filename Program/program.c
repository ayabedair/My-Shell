#include "program.h"
#include "../Redirection/redirection.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

#include "../myCommands/mycat.h"
#include "../myCommands/myecho.h"
#include "../myCommands/mymv.h"
#include "../myCommands/myrm.h"
#include "../myCommands/mycp.h"
#include "../myCommands/mypwd.h"
#include "../myCommands/mycd.h"
#include "../myCommands/mygrep.h"
#include "../myCommands/myenv.h"

#define MAX_CMD_SIZE  1024
#define BOLD_MAGENTA   "\x1b[35m\x1b[1m"
#define BOLD_YELLOW     "\x1b[33m\x1b[1m"
#define COLOR_RESET     "\x1b[0m"

void printPrompt() {
    // Get the username
    char *user = getlogin();
    if (user == NULL) {
        perror("getlogin error");
        exit(EXIT_FAILURE);
    }

    // Get host name
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname error");
        exit(EXIT_FAILURE);
    }

    // Get the current working directory
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd error");
        exit(EXIT_FAILURE);
    }

    // Print the prompt
    printf(BOLD_YELLOW "%s@%s" BOLD_MAGENTA ":%s" COLOR_RESET "> ", user, hostname, cwd);
}

void readCommand(char *cmd, int size) {
	if (fgets(cmd, size, stdin) == NULL) {
            perror("fgets error");
            return; 
        }

        // Remove newline from input
        cmd[strcspn(cmd, "\n")] = '\0';
}

int countArgs(char **args) {
    int count = 0;
    while (args[count] != NULL) {
        count++;
    }
    return count;
}

// Parse the input command
void parseCommand(char *cmd, char **args, char **inFile, char **outFile, char **errFile, int *append, int *inRedirect, int *outRedirect, int *errRedirect) {
    char *token = strtok(cmd, " \n");
    int i = 0;

    *inFile = NULL;
    *outFile = NULL;
    *errFile = NULL;
    *append = 0;
    *inRedirect = 0;
    *outRedirect = 0;
    *errRedirect = 0;

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            // Input redirection
            *inRedirect = 1;
            token = strtok(NULL, " \n");
            if (token != NULL) {
                *inFile = token;
            }
        } else if (strcmp(token, ">") == 0) {
            // Output redirection (overwrite)
            *outRedirect = 1;
            *append = 0;
            token = strtok(NULL, " \n");
            if (token != NULL) {
                *outFile = token;
            }
        } else if (strcmp(token, ">>") == 0) {
            // Output redirection (append)
            *outRedirect = 1;
            *append = 1;
            token = strtok(NULL, " \n");
            if (token != NULL) {
                *outFile = token;
            }
        } else if (strcmp(token, "2>") == 0) {
            // Standard error redirection (overwrite)
            *errRedirect = 1;
            *append = 0;
            token = strtok(NULL, " \n");
            if (token != NULL) {
                *errFile = token;
            }
        } else if (strcmp(token, "2>>") == 0) {
            // Standard error redirection (append)
	    *errRedirect = 1;
            *append = 1;
            token = strtok(NULL, " \n");
            if (token != NULL) {
                *errFile = token;
            }
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
}


void runCommand(int argc, char **args, char *inFile, char *outFile, char *errFile, int append, int inRedirect, int outRedirect, int errRedirect) {

	int status;
	pid_t pid = fork();
	if(pid < 0) {
		perror("fork error");
                exit(EXIT_FAILURE);
	} else if (pid == 0) {
   		handleRedirection(inFile, outFile, errFile, append, inRedirect, outRedirect, errRedirect);

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
        	} else if (strcmp(args[0], "mygrep") == 0) {
			runMygrep(argc, args);
		} else if (strcmp(args[0], "myenv") == 0) {
                        runMyenv(argc, args);
                }else {
			execvp(args[0], args);
	                printf("execvp error");
        	        exit(EXIT_FAILURE);
		}
		exit(0);
	}else {
		wait(&status);
	}

}
