#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "myCommands/mycat.h"
#include "myCommands/myecho.h"
#include "myCommands/mymv.h"
#include "myCommands/myrm.h"
#include "myCommands/mycp.h"
#include "myCommands/mypwd.h"
#include "myCommands/mycd.h"
#include "myCommands/mygrep.h"
#include "myCommands/myenv.h"
#include "Redirection/redirection.h"
#include "Piping/piping.h"
#include "Program/program.h"
#include <limits.h>

#define MAX_CMD_SIZE  1024
#define MAX_ARG_SIZE  150

int main() {
    char cmd[MAX_CMD_SIZE];
    char *args[MAX_ARG_SIZE];
    int status;
    char *inFile, *outFile, *errFile;
    int append, inRedirect, outRedirect, errRedirect, piping_flag;
    while (1) {
 	printPrompt();       

	readCommand(cmd, sizeof(cmd));

	// Skip new-line
	if (cmd[0] == '\0') {
            continue;
        }

	// Check for piping
	piping_flag = hasPiping(cmd);
        if(piping_flag) {
		char *cmd1_args[MAX_CMD_SIZE], *cmd2_args[MAX_CMD_SIZE];
        	handlePiping(cmd, cmd1_args, cmd2_args);
	}else{
        // Parse the input command
        parseCommand(cmd, args, &inFile, &outFile, &errFile, &append, &inRedirect, &outRedirect, &errRedirect);
        // Count the number of arguments
        int argc = countArgs(args);
	// Execute command
        runCommand(argc, args, inFile, outFile, errFile, append, inRedirect, outRedirect, errRedirect);
	}
   }
    return 0;
}
