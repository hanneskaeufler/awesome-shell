#include <stdio.h>
#include <string.h> // for strcmp

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

/**
 * Assert the length of an array
 * https://stackoverflow.com/a/14015976/1777136
 */
void assert_count(int expected, char **arr, char *message) {
    int count = 0;
    for (int i = 0; arr[i] != NULL; i++) {
        count = i + 1;
    }

    int res = expected == count;
    assert_true(res, message);

    if (res == 0) {
        printf("\t-------------------------------------------------\n");
        printf("\t \"%d\" is not equal to \"%d\"\n", count, expected);
        printf("\t-------------------------------------------------\n");
    }
}
