# Library Record Manager

A terminal-based C project that manages books, authors and their relationships using two data-structure implementations.

## Features

- Add, search and delete author and book records.
- Associate books with authors and track author book counts.
- Load and save records in local text files.
- Compare a dynamic-array implementation with a linked-list implementation.

## Build

Requires a C compiler and Make.

```sh
make
```

## Run

Each program reads and writes `authors.txt`, `book.txt` and `writes.txt` in its working directory. Run from the corresponding source directory:

```sh
# Dynamic arrays
cd Project
../build/library-arrays
```

Or, from the repository root:

```sh
# Linked lists
cd "Project - Lists"
../build/library-lists
```

Use menu options 1–6 to manage records and option 7 to save and exit. **Back up the sample text files before experimenting:** saving overwrites the data in the active directory.

## Structure

| Directory | Implementation |
| --- | --- |
| `Project/` | Dynamically allocated arrays |
| `Project - Lists/` | Linked lists |
| `build/` | Local executables, ignored by Git |

The entry points include their implementation files directly; build each entry point only once. This learning project still needs stronger input validation, allocation checks and broader memory-safety testing. The two versions share a record format but use separate fixture files.

Run `make clean` to remove generated executables. CI checks compilation; it does not validate every interactive data-management operation.
