all:
	clang -Wall src/shell.c src/shell_lib.c -o shell

test:
	clang -Wall \
	src/shell_lib.c specs/shell_specs.c specs/test_helper.c \
	-o shell_specs && \
	./shell_specs

.PHONY: all test
