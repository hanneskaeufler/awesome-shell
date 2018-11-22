#include <stdio.h>
#include <string.h> // for strcmp

/**
 * Stupid simple assert_true with epic output
 */
int assert_true(int truthy_value, char *message) {
    if (truthy_value) {
        printf("✅  - %s\n", message);
        return 1;
    }

    printf("❌  - %s\n", message);
    return 0;
}

/**
 * Equals with strings
 */
int assert_equals(const char *expected, const char *actual, char *message) {
    int res = strcmp(expected, actual);
    int success = assert_true(res == 0, message);

    if (res != 0) {
        printf("\t-------------------------------------------------\n");
        printf("\t \"%s\" is not equal to \"%s\"\n", actual, expected);
        printf("\t-------------------------------------------------\n");
    }

    return success;
}

/**
 * Assert the length of an array
 * https://stackoverflow.com/a/14015976/1777136
 */
int assert_count(int expected, char **arr, char *message) {
    int count = 0;
    int i;
    for (i = 0; arr[i] != NULL; i++) {
        count = i + 1;
    }

    int res = expected == count;
    int success = assert_true(res, message);

    if (res == 0) {
        printf("\t-------------------------------------------------\n");
        printf("\t \"%d\" is not equal to \"%d\"\n", count, expected);
        printf("\t-------------------------------------------------\n");
    }

    return success;
}

int all_tests_passed(int results[], int num) {
    int sum = 0;
    int i;

    for (i = 0; results[i] < num; i++) {
        sum += results[i];
    }

    return sum == num;
}
