#include <stdio.h>
#include "shell_lib.h"

/**
 * Stupid simple assert_true with epic output
 */
void assert_true(int truthy_value, char *message)
{
    if (truthy_value)
    {
        printf("✅  - %s\n", message);
    }
    else
    {
        printf("❌  - %s\n", message);
    }
}

int main(int argc, char **arghv)
{
    assert_true(1 == 1, "Something worked");
    assert_true(0 == 0, "Something broke");

    return 0;
}
