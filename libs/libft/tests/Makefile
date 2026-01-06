# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 17:53:05 by hazunic           #+#    #+#              #
#    Updated: 2025/11/19 19:48:23 by hazunic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# tests/Makefile

CC              := cc
CFLAGS          := -Wall -Wextra -Werror
CPPFLAGS        :=

ifeq ($(LEAK_TEST),1)
CPPFLAGS += -DLEAK_TEST
endif

# Where the library lives
LIBFT_DIR       := ..
LIBFT_A         := $(LIBFT_DIR)/libft.a
LIBFT_INC       := -I$(LIBFT_DIR)/inc

# Criterion flags (try pkg-config first, then fallback)
CRIT_CFLAGS     := $(shell pkg-config --cflags criterion 2>/dev/null)
CRIT_LDFLAGS    := $(shell pkg-config --libs criterion 2>/dev/null)
ifeq ($(CRIT_LDFLAGS),)
CRIT_LDFLAGS    := -lcriterion
endif

# Where tests live
# test_memcmp.c 
TEST_SRCS       := test_ftctype.c test_ftmemory.c
TEST_OBJS       := $(TEST_SRCS:.c=.o)

# Helpers
UTILS_DIR		:= utils
UTILS_HEADERS	:=

NAME             := libft_unit_tests

# Allow passing extra options to Criterion (e.g., --filter, -s)
TEST_OPTS       ?=


# Add near the top (or override from CLI)
# VALGRIND_FLAGS ?= \
#   --leak-check=full \
#   --show-leak-kinds=definite,indirect,possible \
#   --errors-for-leak-kinds=definite,indirect,possible \
#   --track-origins=yes \
#   --quiet \
#   --log-file=valgrind-%p.log \
#   --error-exitcode=99

VALGRIND_FLAGS ?= \
				  --leak-check=full \
				  --track-origins=yes \
				  --trace-children=yes \
				  --show-leak-kinds=all \
				  --errors-for-leak-kinds=definite,indirect,possible \
                  --log-file=vlg_logs/valgrind-%p.log \
				  --quiet \
				  --error-exitcode=99 \
                  --suppressions=valgrind.supp

# --quiet 
# VALGRIND toggle: make run VALGRIND=1
# --show-reachable=yes

ifeq ($(VALGRIND),1)
RUNNER := valgrind $(VALGRIND_FLAGS) #--gen-suppressions=all ./libft_unit_tests 2>gen.supp
else
RUNNER :=
endif

LEAK_PROBE := leak_probe

.PHONY: all run clean fclean re show-valgrind leakcheck

leakcheck: $(LEAK_PROBE)
	$(RUNNER) ./$(LEAK_PROBE) || true
	@echo "----- valgrind.log (first 60 lines) -----"
	@sed -n '1,60p' valgrind.log

show-valgrind:
	@echo "----- valgrind.log -----"
	@-test -f valgrind.log && sed -n '1,200p' valgrind.log || echo "(no valgrind.log)"

# ifeq ($(VALGRIND),1)
# RUNNER := valgrind --leak-check=full --error-exitcode=99 2>/dev/null
# endif
#fails on errors (--error-exitcode), noz showing details.

all: $(NAME)

$(NAME): $(LIBFT_A) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT_A) $(CRIT_CFLAGS) $(CRIT_LDFLAGS) -o $@

# %.o: %.c $(UTILS_HEADERS)
# 	$(CC) $(CFLAGS) $(LIBFT_INC) -I$(UTILS_HEADERS) -c $< -o $@

# IMPORTANT: compile with CRIT_CFLAGS so <criterion/criterion.h> resolves
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CRIT_CFLAGS) $(LIBFT_INC) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR) all

run: $(NAME)
	./$(NAME) -j --order=random --color=always --verbose


clean:
	rm -f $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f vlg_logs/valgrind-*.log

re: fclean all

# run tests in random order everytime to catch hidden dependencies like “test B only passes if test A ran before”.
#./$(NAME) -j --order=random --verbose

# usage: ./libft_unit_tests OPTIONS
# options: 
#     -h or --help: prints this message
#     -q or --quiet: disables all logging
#     -v or --version: prints the version of criterion these tests have been linked against
#     -l or --list: prints all the tests in a list
#     -jN or --jobs N: use N concurrent jobs
#     -f or --fail-fast: exit after the first failure
#     --color=<auto|always|never>: colorize the output
#     --encoding=<ENCODING>: use the specified encoding for the output (default: locale-deduced)
#     --ascii: don't use fancy unicode symbols or colors in the output
#     -S or --short-filename: only display the base name of the source file on a failure
#     --filter [PATTERN]: run tests matching the given pattern
#     --timeout [TIMEOUT]: set a timeout (in seconds) for all tests
#     --tap[=FILE]: writes TAP report in FILE (no file or "-" means stderr)
#     --xml[=FILE]: writes XML report in FILE (no file or "-" means stderr)
#     --json[=FILE]: writes JSON report in FILE (no file or "-" means stderr)
#     --always-succeed: always exit with 0
#     --verbose[=level]: sets verbosity to level (1 by default)
#     --crash: crash failing assertions rather than aborting (for debugging purposes)
#     --debug[=TYPE]: run tests with a debugging server, listening on localhost:1234 by default. TYPE may be gdb, lldb, or wingbd.
#     --debug-transport=VAL: the transport to use by the debugging server. `tcp:1234` by default
#     --full-stats: Tests must fully report statistics (causes massive slowdown for large number of assertions but is more accurate).
#     --ignore-warnings: Ignore warnings, do not exit with a non-zero exit status.
#     -OP:F or --output=PROVIDER=FILE: write test report to FILE using the specified provider

# TESTING OPTIONS

# run: $(NAME)
# @rm -f valgrind-*.log
# 	./$(NAME) $(TEST_OPTS)

# run: $(NAME)
# 	$(RUNNER) ./$(NAME) $(TEST_OPTS)

# run: $(NAME)
# 	$(RUNNER) ./$(NAME) $(TEST_OPTS)
# ifeq ($(VALGRIND),1)
# 	@echo "----- Valgrind logs (first 80 lines each) -----"
# 	@ls -1 valgrind-*.log 2>/dev/null | xargs -r -I{} sh -c 'echo "=== {} ==="; sed -n "1,80p" {}; echo'
# endif
# $(RUNNER) ./$(NAME) --verbose $(TEST_OPTS)
# -j




#make -C tests run VALGRIND=1 TEST_OPTS="--verbose -j1" (single job is nicer for Valgrind).