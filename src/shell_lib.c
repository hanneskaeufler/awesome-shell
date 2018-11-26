#include <string.h> // for strtok
#include <sys/wait.h> // for that waitpid stuff
#include <stdio.h> // for teh printf
#include <unistd.h> // fork comes from there
#include <stdlib.h> // for EXIT_FAILURE
#include "shell_lib.h"

#define ASH_TOK_DELIM " "

/**
 * Split a line of commands into tokens separated by empty space
 */
char **ash_split_line(char *line) {
    int bufsize = 64, position = 0;
    char **tokens = malloc(sizeof(char*) * bufsize);
    char *token = strtok(line, ASH_TOK_DELIM);
    tokens[position] = token;

    while (token != NULL) {
        tokens[position] = token;
        position++;
        token = strtok(NULL, ASH_TOK_DELIM);
    }

    tokens[position] = NULL; // NULL terminating the array

    return tokens;
}

/**
 * https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c
 */
#define ASH_RL_BUFSIZE 64
char *ash_read_line(int (*getchar_fn)()) {
    int bufsize = ASH_RL_BUFSIZE;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;
    int position = 0;

    while (1) {
        c = (*getchar_fn)();

        if (c == '\n') {
            buffer[position] = '\0'; // Terminate with 0 character
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += ASH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
        }
    }

    return buffer;
}

/**
 * Execute the parsed command and return with status
 */
int ash_execute_command(char **args) {
    pid_t pid;
    int status;
    pid = fork();

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("ash");
        }

        exit(EXIT_FAILURE);
    } else {
        pid_t wpid;
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
    char **args;
    int status;

    do {
        printf("> ");
        line = ash_read_line(getchar);
        args = ash_split_line(line);
        status = ash_execute_command(args);

        free(line); // free alloced memory from ash_read_line
        free(args); // free alloced memory from ash_split_line
    } while (status);
}
