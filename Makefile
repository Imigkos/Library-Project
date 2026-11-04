CC ?= cc
CFLAGS ?= -std=gnu11 -Wall -Wextra -g

.PHONY: all clean
all: build/library-arrays build/library-lists

build/library-arrays: Project/main.c Project/main_functions.c Project/init.h
	mkdir -p build
	$(CC) $(CFLAGS) Project/main.c -o $@

build/library-lists: Project\ -\ Lists/lists_main.c Project\ -\ Lists/lists_functions.c Project\ -\ Lists/init.h
	mkdir -p build
	$(CC) $(CFLAGS) "Project - Lists/lists_main.c" -o $@

clean:
	rm -rf build
