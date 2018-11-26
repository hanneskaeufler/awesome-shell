int assert_true(int truthy_value, char *message);
int assert_equals(const char *expected, const char *actual, char *message);
int assert_count(int expected, char **arr, char *message);
int all_tests_passed(int results[], int num);
