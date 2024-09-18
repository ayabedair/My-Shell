#ifndef PIPING_H_
#define PIPING_H_

int hasPiping(char *cmd);
void parse_command(char *cmd, char **args);
void execute_command(char **args);
void handlePiping(char *cmd, char **cmd1_args, char **cmd2_args);


#endif
