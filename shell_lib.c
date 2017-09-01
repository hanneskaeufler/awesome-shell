#include <stdlib.h>
#include <stdio.h>

/**
 * Execute the parsed command and return with status
 */
int execute_command()
{
    return 0;
}

/**
 * Performs the infinite loop until we kill the shell
 */
void input_loop()
{
    int status;

    do {
        printf("> ");
        status = execute_command();
    } while (status);
}
