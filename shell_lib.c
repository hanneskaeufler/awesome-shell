#include <sys/wait.h> // for that waitpid stuff
#include <stdio.h> // for teh printf
#include <unistd.h> // fork comes from there
#include <stdlib.h> // for EXIT_FAILURE
#include "shell_lib.h"

/**
 * Execute the parsed command and return with status
 */
int ash_execute_command(char **args) {
    pid_t pid, wpid;
    int status;
    pid = fork();

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shellds");
        }

        exit(EXIT_FAILURE);
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
 * Performs the infinite loop until we kill the shell
 */
void ash_input_loop() {
    char **args = NULL;
    int status;

    do {
        printf("> ");
        status = ash_execute_command(args);
    } while (status);
}
