#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "../myCommands/mycat.h"
#include "../myCommands/myecho.h"
#include "../myCommands/mymv.h"
#include "../myCommands/myrm.h"
#include "../myCommands/mycp.h"
#include "../myCommands/mypwd.h"
#include "../myCommands/mycd.h"
#include "../myCommands/mygrep.h"
#include "../myCommands/myenv.h"
#include "piping.h"

int hasPiping(char *cmd) {
    // Check if the pipe character '|' exists in the command string
    return strchr(cmd, '|') != NULL;
}

void parse_command(char *cmd, char **args) {
    char *token;
    int i = 0;
    token = strtok(cmd, " \n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
}

void execute_command(char **args) {
    if (execvp(args[0], args) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

void handlePiping(char *cmd, char **cmd1_args, char **cmd2_args) {

	int pipefd[2];
	pid_t pid1, pid2;
	char *pipe_pos = strchr(cmd, '|');
        if (pipe_pos != NULL) {
            *pipe_pos = '\0'; // Terminate the first command
            pipe_pos++; // Skip the pipe symbol

            // Parse the first and second command
            parse_command(cmd, cmd1_args);
            parse_command(pipe_pos, cmd2_args);

            // Create a pipe
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            // Fork the first child process
            if ((pid1 = fork()) == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

	    if (pid1 == 0) { // Child process for the first command
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
                close(pipefd[1]);
                execute_command(cmd1_args);
            }

            // Fork the second child process
            if ((pid2 = fork()) == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (pid2 == 0) { // Child process for the second command
                close(pipefd[1]); 
                dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from pipe
                close(pipefd[0]); 
                execute_command(cmd2_args);
            }
	
	    // Close both ends of the pipe in the parent process
            close(pipefd[0]);
            close(pipefd[1]);

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

	}

}
