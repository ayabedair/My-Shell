#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void runMyenv(int argc, char **args) { 
    if (argc == 1) {
        for (int i = 0; environ[i] != NULL; i++) {
            printf("environ[%d] = %s\n", i, environ[i]);
        }
    } else if (argc == 2) {
        char *var = getenv(args[1]);
        if (var != NULL) {
            printf("%s=%s\n", args[1], var);
        } else {
            printf("Variable %s not found.\n", args[1]);
        }
    } else {
        printf("Usage: myenvir [variable_name]\n");
    }
}

