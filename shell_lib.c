#include <sys/wait.h> // for that waitpid stuff
#include <stdio.h> // for teh printf
#include <unistd.h> // fork comes from there
#include <stdlib.h> // for EXIT_FAILURE
#include "shell_lib.h"

/**
 * https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c
 */
char *ash_read_line(int (*getchar_fn)()) {
    int bufsize = 1;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;
    int position = 0;

    while (1) {
        c = (*getchar_fn)();

        if (c == '\n') {
            buffer[position] =  '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
    }

    /* if (position >= bufsize) { */
    /*     bufsize += 1024; */
    /*     buffer = realloc(buffer, bufsize); */
    /* } */

    return buffer;
}

/**
 * Execute the parsed command and return with status
 */
int ash_execute_command(char **args) {
    pid_t pid, wpid;
    int status;
    pid = fork();

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("ash");
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
    char *line;
    char **args = NULL;
    int status;

    do {
        printf("> ");
        line = ash_read_line(getchar);
        *args = line;
        status = ash_execute_command(args);

        // cleanup. I dont really understand this yet.
        free(line);
        free(args);
    } while (status);
}
