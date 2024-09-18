#ifndef PROG_H_
#define PROG_H_

void printPrompt();
void readCommand(char *cmd, int size);
int countArgs(char **args);
void parseCommand(char *cmd, char **args, char **inFile, char **outFile, char **errFile, int *append, int *inRedirect, int *outRedirect, int *errRedirect);
// void runCommand(int argc, char **args, char *inFile, char *outFile, char *errFile, int *append, int *inRedirect, int *outRedirect, int *errRedirect);
void runCommand(int argc, char **args, char *inFile, char *outFile, char *errFile, int append, int inRedirect, int outRedirect, int errRedirect);

#endif

