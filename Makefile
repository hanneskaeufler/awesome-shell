CC ?= clang
CFLAGS ?= -Wall -Wextra -pedantic
DEPS ?= src/shell_lib.h

shell.o: src/shell.c
	$(CC) -c $(CFLAGS) src/shell.c

shell_lib.o: src/shell_lib.c src/shell_lib.h
	$(CC) -c $(CFLAGS) src/shell_lib.c

shell: shell.o shell_lib.o
	$(CC) $(CFLAGS) shell.o shell_lib.o -o shell

shell_specs.o: specs/shell_specs.c specs/test_helper.h
	$(CC) -c $(CFLAGS) specs/shell_specs.c

test_helper.o: specs/test_helper.c
	$(CC) -c $(CFLAGS) specs/test_helper.c

shell_specs: shell_specs.o shell_lib.o test_helper.o
	$(CC) $(CFLAGS) shell_lib.o test_helper.o shell_specs.o -o shell_specs

all: shell

test: shell_specs
	./shell_specs

bundle:
	bundle install

test-integration: bundle all
	bundle exec rspec --format=documentation integration_spec.rb

clean:
	-rm *.o shell shell_specs

.PHONY: clean test test-integration
