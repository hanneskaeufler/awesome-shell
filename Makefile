all:
	clang -Wall shell.c shell_lib.c -o shell

test:
	clear && clang -Wall shell_lib.c shell_specs.c test_helper.c -o shell_specs && ./shell_specs

.PHONY: all test
