#include <stdio.h>
#include <string.h> // for strcmp
#include "shell_lib.h"

/**
 * Testdouble for the "perror" from ... somewhere
 */
char *last_perror = "";

void perror(const char *s)
{
    last_perror = strdup(s);
}

/**
 * Stupid simple assert_true with epic output
 */
void assert_true(int truthy_value, char *message) {
    if (truthy_value) {
        printf("✅  - %s\n", message);
    }
    else {
        printf("❌  - %s\n", message);
    }
}

/**
 * Equals with strings
 */
void assert_equals(const char *expected, const char *actual, char *message) {
    int res = strcmp(expected, actual);
    assert_true(res == 0, message);

    if (res != 0) {
        printf("\t-------------------------------------------------\n");
        printf("\t \"%s\" is not equal to \"%s\"\n", actual, expected);
        printf("\t-------------------------------------------------\n");
    }
}

int main(int argc, char **arghv) {

    // arrange
    char **unknown_cmd = (char *[]){ "ajsfkjalkfjsaklfjaks" };
    const char *expected = "executing failed";
    // act
    execute_command(unknown_cmd);
    // assert
    assert_equals(expected, last_perror, "Executing an unknown command prints error");

    // arrange
    char **successfull_cmd = (char *[]){ "true" };
    const char *expected_succ = "";
    // act
    execute_command(successfull_cmd);
    // assert
    assert_equals(expected_succ, last_perror, "Executing a known command does not print and error");

    return 0;
}
