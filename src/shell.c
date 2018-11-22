#include <stdlib.h>
#include <stdio.h>
#include "shell_lib.h"

int main(int argc __attribute__ ((unused)), char **arghv __attribute__ ((unused)))
{
    ash_input_loop();

    return EXIT_SUCCESS;
}
