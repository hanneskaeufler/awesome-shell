#include <stdlib.h>
#include <stdio.h>

/**
 * Performs the infinite loop until we kill the shell
 */
void input_loop()
{
    int status;

    do {
        printf("> ");
        status = 0;
    } while (status);
}

int main(int argc, char **arghv)
{
    input_loop();

    return EXIT_SUCCESS;
}
