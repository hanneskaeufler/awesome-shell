#include <sys/wait.h> // for that waitpid stuff
#include <stdio.h> // for teh printf
#include <unistd.h> // fork comes from there
#include <stdlib.h> // for EXIT_FAILURE

/**
 * Execute the parsed command and return with status
 */
int execute_command() {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        exit(EXIT_FAILURE);
    }

    return 0;
}

/**
 * Performs the infinite loop until we kill the shell
 */
void input_loop() {
    int status;

    do {
        printf("> ");
        status = execute_command();
    } while (status);
}
