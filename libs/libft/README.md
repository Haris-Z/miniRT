# Libft – General Purpose C Utility Library

> Re-implementation of a subset of the C standard library and other utilities,
> intended as a reusable foundation for 42 projects and personal C code.

---

## Overview

`libft` is a static library (`libft.a`) providing:

- Character classification and conversion (`ft_ctype`)
- Memory manipulation (`ft_mem`)
- String utilities (`ft_string`)
- Numeric conversion and helpers (`ft_utils`)
- Simple I/O helpers (`ft_io`)
- Singly linked lists (`ft_slist`)
- A line reader (`get_next_line`)
- Basic error reporting helpers (`ft_error`)

The goal is to offer a well-tested, well-documented subset of commonly used
glibc-like functions.

---

## Modules

Each functional area is organized as a Doxygen group:

- **Character classification** – `ft_ctype`  
  `ft_isalpha`, `ft_isdigit`, `ft_tolower`, …

- **Memory operations** – `ft_mem`  
  `ft_memset`, `ft_memcpy`, `ft_memmove`, `ft_memcmp`, …

- **String utilities** – `ft_string`  
  `ft_strlen`, `ft_strchr`, `ft_strdup`, `ft_strjoin`, …

- **Utility functions** – `ft_utils`  
  `ft_atoi`, `ft_atol`, `ft_calloc`, `ft_split`, `ft_itoa`, …

- **I/O helpers** – `ft_io`  
  `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

- **Singly linked list API** – `ft_slist`  
  `ft_lstnew`, `ft_lstadd_back`, `ft_lstclear`, …

- **Line reader** – `ft_getline`  
  `get_next_line` for reading from file descriptors.

- **Error handling utilities** – `ft_error`  
  Small helpers for consistent error messages / codes.

For details, see **Modules → [group pages]** in the generated Doxygen docs.

---

## Usage

### Building the library

```bash
# Build libft.a
make

# Build with debug symbols
make DEBUG=1

# Build with AddressSanitizer
make SAN=1

# Build demo executable linked against libft
make demo
./libft_demo

# Linking against libft
cc main.c -I/path/to/libft/inc -L/path/to/libft -lft -o my_program

```

## Project Structure

```text
libft/
  inc/
    libft.h          # Public header (prototypes, documentation groups)
  src/
    ft_ctype/        # Character classification and conversion
    ft_mem/          # Memory operations
    ft_string/       # String helpers
    ft_utils/        # Converters, allocators, misc utilities
    ft_io/           # File descriptor-based I/O helpers
    ft_slist/        # Singly linked list implementation
    ft_getline/      # get_next_line()
    ft_error/        # Error reporting helpers
    demo/            # Optional: small demo program
  tests/
    ...              # Criterion tests, valgrind configs, etc.
  Doxyfile
  Makefile
  README.md
```

## Testing

The project includes a separate tests/ Makefile to run unit tests:

```bash
# Run default test suite
make test

# Run tests with valgrind and leak checks
make test-vlg

# Clean test artifacts
make test-clean
```

## Ddocumentation

```bash
# Create Docs
# run the command - generate docs into docs/html/
# index.html will be created at root of repo -> open in browser
make docs
```

## TODO

- [ ] add ft_printf
- [ ] finish headerfile docs
