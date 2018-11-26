#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for strcmp
#include "../src/shell_lib.h"
#include "test_helper.h"

/**
 * Testdouble for the "perror" from ... somewhere
 */
void perror(const char *s __attribute__ ((unused)))
{
}

/**
 * Configurable testdouble for getchar()
 */
int did_read_char_count = 0;
char *cmd_to_read = "";
int fake_getchar() {
    int c = cmd_to_read[did_read_char_count];
    did_read_char_count++;
    return c;
}

int main(int argc __attribute__ ((unused)), char **arghv __attribute__ ((unused))) {
    int results[7];

    // arrange
    did_read_char_count = 0;
    cmd_to_read = "ls\n";
    const char *expected_cmd = "ls";
    // act
    char *cmd = ash_read_line(fake_getchar);
    // assert
    results[0] = assert_equals(expected_cmd, cmd, "Reading the line must return the chars that make up the command");
    // teardown
    free(cmd);

    // -----------------

    // arrange
    did_read_char_count = 0;
    cmd_to_read = "letsseeifthisworkswithsuperlongcommands\n"; // this is 41 chars I think so 41 * 1 (1 because sizeof(char) is 1) bytes = 41 bytes? fitting into ASH_RL_BUFSIZE
    const char *expected_long_cmd = "letsseeifthisworkswithsuperlongcommands";
    // act
    char *long_cmd = ash_read_line(fake_getchar);
    // assert
    results[1] = assert_equals(expected_long_cmd, long_cmd, "Reading long commands works");
    // teardown
    free(long_cmd);

    // -----------------
    // arrange
    did_read_char_count = 0;
    cmd_to_read = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n"; // this is 150 chars I think so 150 * 1 bytes = 150 bytes? Not fitting into ASH_RL_BUFSIZE and having to reallocate
    const char *expected_super_long_cmd = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
    // act
    char *super_long_cmd = ash_read_line(fake_getchar);
    // assert
    results[2] = assert_equals(expected_super_long_cmd, super_long_cmd, "Reading super long commands works");
    // teardown
    free(long_cmd);

    // -----------------

    // arrange
    char **any_cmd = (char *[]){ "ls" };
    // act, assert
    results[3] = assert_true(ash_execute_command(any_cmd) == 1, "ash_execute_command returns 1");

    // -----------------

    // arrange
    const char *line = "ls -a";
    // act
    char **res = ash_split_line(strdup(line));
    // assert
    results[4] = assert_count(2, res, "It must split into two parts");
    results[5] = assert_equals("ls", res[0], "It must split to ls at the empty space");
    results[6] = assert_equals("-a", res[1], "It must split to -a at the empty space");
    // teardown
    free(res);

    /* if (all_tests_passed(results, 1)) { */
    /*     return 0; */
    /* } */

    return 0;
}
