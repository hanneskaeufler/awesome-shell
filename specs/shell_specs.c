#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for strcmp
#include "../src/shell_lib.h"
#include "test_helper.h"

/**
 * Testdouble for the "perror" from ... somewhere
 */
void perror(const char *s)
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
    // act, assert
    assert_true(ash_execute_command(any_cmd) == 1, "ash_execute_command returns 1");

    // -----------------

    // arrange
    const char *line = "ls -a";
    // act
    char **res = ash_split_line(strdup(line));
    // assert
    assert_count(2, res, "It must split into two parts");
    assert_equals("ls", res[0], "It must split to ls at the empty space");
    assert_equals("-a", res[1], "It must split to -a at the empty space");
    free(*res); // no clue if this is needed

    return 0;
}
