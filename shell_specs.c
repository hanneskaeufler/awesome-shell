#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for strcmp
#include "shell_lib.h"

/**
 * Testdouble for the "perror" from ... somewhere
 */
void perror(const char *s)
{
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

int did_read_char_count = 0;
char *cmd_to_read = "";
int fake_getchar() {
    int c = cmd_to_read[did_read_char_count];
    did_read_char_count++;
    return c;
}

int main(int argc, char **arghv) {

    // arrange
    did_read_char_count = 0;
    cmd_to_read = "ls\n";
    const char *expected_cmd = "ls";
    // act
    char *cmd = ash_read_line(fake_getchar);
    // assert
    assert_equals(expected_cmd, cmd, "Reading the line must return the chars that make up the command");

    // -----------------

    // arrange
    did_read_char_count = 0;
    cmd_to_read = "letsseeifthisworkswithsuperlongcommands\n"; // this is 41 chars I think so 41 * 8 (8 because 64 bit? else 4) bytes = 328 bytes?
    const char *expected_long_cmd = "letsseeifthisworkswithsuperlongcommands";
    // act
    char *long_cmd = ash_read_line(fake_getchar);
    // assert
    assert_equals(expected_long_cmd, long_cmd, "Reading super long commands works");


    // -----------------

    // arrange
    char **any_cmd = (char *[]){ "ls" };
    // act
    assert_true(ash_execute_command(any_cmd) == 1, "ash_execute_command returns 1");
    // assert

    return 0;
}
