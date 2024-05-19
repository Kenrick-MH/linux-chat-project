# Default goal
all: client-tests

# Find all .c and .h files in the ../../client directory
CLIENT_FILES := $(wildcard ../../client/*.c ../../client/*.h)

# Build client-tests
client-tests: test_runner.c $(CLIENT_FILES)
	gcc -g -o $@ $^

# Clean up generated files
clean:
	rm -f client-tests

# Indicate that these targets are not actual files
.PHONY: all clean
