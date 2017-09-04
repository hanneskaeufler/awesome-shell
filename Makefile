CC ?= clang

all:
	clang -Wall src/shell.c src/shell_lib.c -o shell

test:
	$(CC) -Wall \
	src/shell_lib.c specs/shell_specs.c specs/test_helper.c \
	-o shell_specs && \
	./shell_specs

bundle:
	bundle install

test-integration: bundle
	bundle exec rspec --format=documentation integration_spec.rb

.PHONY: all test test-integration
