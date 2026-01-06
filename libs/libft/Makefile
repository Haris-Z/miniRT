# **************************************************************************** #
#                                   libft                                      #
# **************************************************************************** #

# ============================================================================ #
#                               COLOR SETTINGS                                 #
# ============================================================================ #

# Colors
GREEN		:= \033[0;32m
BLUE		:= \033[0;34m
YELLOW		:= \033[1;33m
RED			:= \033[0;31m
MAGENTA		:= \033[0;35m
CYAN		:= \033[0;36m
GRAY		:= \033[0;90m

# Style/Reset
BOLD		:= \033[1m
DIM			:= \033[2m
ULINE		:= \033[4m
RESET		:= \033[0m

# Icons / Emojis
OK_ICON		:= ✔
WARN_ICON	:= ●
ERR_ICON	:= ✗
BUILD_ICON	:= 🔧
DOC_ICON	:= 📚

# ============================================================================ #
#                                  MESSAGES                                    #
# ============================================================================ #

LIB_MSG       = @echo "$(GREEN)[$(OK_ICON)] Build succeeded $(RESET) → $(BOLD)$(NAME)$(RESET)"
EXEC_MSG      = @echo "$(GREEN)$(OK_ICON) Executable built → $(NAME)$(RESET)"
RE_MSG        = @echo "$(BLUE)[$(WARN_ICON)] Rebuilt..  → $(RESET) $(NAME) "

# Compile messages
COMPILE_MSG   = @echo "$(CYAN)[$(BUILD_ICON)] Compiled →$(RESET) $<"

# Cleanup messages
CLEAN_OBJ_MSG = @echo "$(RED)[$(WARN_ICON)] Deleting object files ...$(RESET)"
CLEAN_OK_OBJ  = @echo "$(GREEN)[$(ERR_ICON)]$(RESET) Object files removed."

CLEAN_BIN_MSG = @echo "$(RED)[$(WARN_ICON)] Deleting archive ... $(RESET)"
CLEAN_OK_BIN  = @echo "$(GREEN)[$(ERR_ICON)]$(RESET) Archive removed → $(NAME)."

# Static Analysis messages
CPPCHECK_MSG  = @echo "$(YELLOW)[$(WARN_ICON)] Running static analysis with cppcheck...$(RESET)"

# Docs-related messages
DOCS_GEN_MSG  = @echo "$(MAGENTA)[$(DOC_ICON)] Generating Doxygen docs...$(RESET)"
DOCS_AT_MSG   = @echo "$(MAGENTA)[$(DOC_ICON)] Docs at $(DOCS_OUT)$(RESET)"
DOCS_OPEN_MSG = @echo "$(MAGENTA)[$(DOC_ICON)] Opening docs...$(RESET)"
DOCS_RM_MSG   = @echo "$(MAGENTA)[$(DOC_ICON)] Removing generated docs...$(RESET)"

# ============================================================================ #
#   LIBRARY NAME / PRIMARY TARGET                                              #
# ============================================================================ #
NAME        := libft.a

# ============================================================================ #
#   COMPILER & COMPILER FLAGS                                                  #
# ============================================================================ #
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
LDFLAGS     :=

# ============================================================================ #
#   DEBUG FLAGS                                                                #
# ============================================================================ #
#CC          := cc
#CFLAGS      := -Wall -Wextra -Werror

# ============================================================================ #
#   COMPILER PRE-PROCESSOR OPTIONS                                             #
# ============================================================================ #
# Example
# CPPFLAGS    :=
# $(CPPFLAGS)
# ifeq ($(LEAK_TEST),1) - for testing
# CPPFLAGS += -DLEAK_TEST
# endif
# Debug & sanitizer toggles
# Usage:
#   make DEBUG=1        → adds -g3 -O0
#   make SAN=1          → adds -fsanitize=address (compile + link)
#   make DEBUG=1 SAN=1  → both
DEBUG	?= 0
SAN		?= 0

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -O0
endif

ifeq ($(SAN),1)
	CFLAGS  += -fsanitize=address,undefined -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
endif

# Strings for banner
ifeq ($(DEBUG),1)
	DEBUG_STR := ON
else
	DEBUG_STR := OFF
endif

ifeq ($(SAN),1)
	SAN_STR := ON
else
	SAN_STR := OFF
endif

MODE_MSG = @echo "$(GRAY)[mode] DEBUG=$(DEBUG_STR) SAN=$(SAN_STR) CFLAGS='$(CFLAGS)'$(RESET)"

# ============================================================================ #
#   ARCHIVER / INDEXER (for .a files)                                          #
# ============================================================================ #
# ar program creates, modifies, and extracts from archives.
# 	-s: creates an index to the symbols defined in relocatable object modules
# 		in the archive when you specify the modifier.
AR          := ar
ARFLAGS     := rcs
RANLIB      := ranlib

# ============================================================================ #
#   CLEANUP/UTILITIES                                                          #
# ============================================================================ #
RM          := rm -f
RMDIR       := rm -rf
# ============================================================================ #
#                             PROJECT LAYOUT                                   #
# ============================================================================ #

# Location of sources files
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := inc
# Location of test files
TEST_DIR    := tests

# Public Headers / Include flages
#LIBFT_H      := $(INC_DIR)/
INCLUDES    := -I$(INC_DIR)

# ============================================================================ #
#                        SEARCH PATHS BY MODULE (VPATH)                        #
# ============================================================================ #
# get info on VPATH
# VPATH_FT_CTYPE = src/ft_ctype/

# ============================================================================ #
#  SOURCE LIST (norm compliant)                                                #
# ============================================================================ #
FT_CTYPE_SRC := \
	ft_ctype/ft_isalnum.c \
	ft_ctype/ft_isalpha.c \
	ft_ctype/ft_isascii.c \
	ft_ctype/ft_isblank.c \
	ft_ctype/ft_iscntrl.c \
	ft_ctype/ft_isdigit.c \
	ft_ctype/ft_isgraph.c \
	ft_ctype/ft_islower.c \
	ft_ctype/ft_isprint.c \
	ft_ctype/ft_ispunct.c \
	ft_ctype/ft_isspace.c \
	ft_ctype/ft_isupper.c \
	ft_ctype/ft_isxdigit.c \
	ft_ctype/ft_tolower.c \
	ft_ctype/ft_toupper.c

FT_MEM_SRC := \
	ft_mem/ft_bzero.c \
	ft_mem/ft_memchr.c \
	ft_mem/ft_memcmp.c \
	ft_mem/ft_memcpy.c \
	ft_mem/ft_memmove.c \
	ft_mem/ft_memset.c

FT_STRING_SRC := \
	ft_string/ft_strchr.c \
	ft_string/ft_strdup.c \
	ft_string/ft_striteri.c \
	ft_string/ft_strjoin.c \
	ft_string/ft_strlcat.c \
	ft_string/ft_strlcpy.c \
	ft_string/ft_strlen.c \
	ft_string/ft_strmapi.c \
	ft_string/ft_strncmp.c \
	ft_string/ft_strndup.c \
	ft_string/ft_strnstr.c \
	ft_string/ft_strrchr.c \
	ft_string/ft_strtrim.c \
	ft_string/ft_substr.c

FT_UTILS_SRC := \
	ft_utils/free_mem.c \
	ft_utils/ft_atod.c \
	ft_utils/ft_atof.c \
	ft_utils/ft_atoi.c \
	ft_utils/ft_atol.c \
	ft_utils/ft_calloc.c \
	ft_utils/ft_free_and_null.c \
	ft_utils/ft_itoa.c \
	ft_utils/ft_realloc.c \
	ft_utils/ft_split.c

FT_IO_SRC := \
	ft_io/ft_putchar_fd.c \
	ft_io/ft_putendl_fd.c \
	ft_io/ft_putnbr_fd.c \
	ft_io/ft_putstr_fd.c

FT_SLIST_SRC := \
	ft_slist/ft_lstadd_back.c \
	ft_slist/ft_lstadd_front.c \
	ft_slist/ft_lstclear.c \
	ft_slist/ft_lstdelone.c \
	ft_slist/ft_lstiter.c \
	ft_slist/ft_lstlast.c \
	ft_slist/ft_lstmap.c \
	ft_slist/ft_lstnew.c \
	ft_slist/ft_lstsize.c

FT_GNL_SRC := \
	ft_getline/get_next_line.c

FT_ERROR_SRC := \
	ft_error/errors.c

SRCS_REL := \
	$(FT_CTYPE_SRC) \
	$(FT_MEM_SRC) \
	$(FT_STRING_SRC) \
	$(FT_UTILS_SRC) \
	$(FT_IO_SRC) \
	$(FT_SLIST_SRC) \
	$(FT_GNL_SRC) \
	$(FT_ERROR_SRC)

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS_REL))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#DEP         := $(OBJ:.o=.d)

# ============================================================================ #
#                                  RULES                                       #
# ============================================================================ #
all: $(NAME)

$(NAME): $(OBJS) 
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)
	$(LIB_MSG)
	$(MODE_MSG)
#

# ============================================================================ #
# Compile each .c to its corresponding .o (objects live next to sources)
# ============================================================================ #
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(COMPILE_MSG)

# ============================================================================ #
#                              CLEAN OBJECT FILES                              #
# ============================================================================ #
clean: ## Remove object files and obj/ directory
	$(CLEAN_OBJ_MSG)
	@$(RM) $(OBJS)
	@$(RMDIR) $(OBJ_DIR)
	$(CLEAN_OK_OBJ)

# ============================================================================ #
#                              CLEAN ARCHIVE FILE                              #
# ============================================================================ #
fclean: clean
	$(CLEAN_BIN_MSG)
	@$(RM) $(NAME)
	$(CLEAN_OK_BIN)

# ============================================================================ #
#                          CLEAN ALL GENERATED FILES                           #
# ============================================================================ #
aclean: fclean clean-docs test-clean

# ============================================================================ #
#                           FULL REBUILD (CLEAN + ALL)                         #
# ============================================================================ #
re: fclean all
	$(RE_MSG)

# ============================================================================ #
#                                TEST TARGETS                                  #
# ============================================================================ #
# Test runner (delegates to tests/Makefile)
# Forward VALGRIND and TEST_OPTS down to the test runner.
# Usage:
#   make test
#   make test VALGRIND=1
#   make test TEST_OPTS='-s ft_ctype --filter isalpha'
#   make test TEST_OPTS="--verbose"
#   make -C tests run TEST_OPTS="--verbose"
# ============================================================================ #

test: $(NAME)
	@$(MAKE) -C $(TEST_DIR) run TEST_OPTS="$(TEST_OPTS)"

test-vlg: $(NAME)
	@$(MAKE) -C $(TEST_DIR) run VALGRIND=1 LEAK_TEST=1 TEST_OPTS="--verbose -j1"

test-leak: $(NAME)
	@$(MAKE) -C $(TEST_DIR) run VALGRIND=1 LEAK_TEST=$(LEAK_TEST) TEST_OPTS="--verbose -j1"
#TEST_OPTS="--filter ft_memory::intentional_leak --verbose"

test-log:
	@$(MAKE) -C $(TEST_DIR) show-valgrind

test-clean:
	@$(MAKE) -C $(TEST_DIR) fclean
# ============================================================================ #


# ============================================================================ #
#                           DOCUMENTATION (Doxygen)                            #
# ============================================================================ #
DOXYGEN		?= doxygen
DOCS_OUT	:= docs/html/index.html
DOCS_ROOT	:= index.html

docs: ## Generate Doxygen documentation
	$(DOCS_GEN_MSG)
	@$(DOXYGEN) Doxyfile
	$(DOCS_AT_MSG)
	@# Create a root-level index.html pointing to docs/html/index.html
	@if command -v ln >/dev/null 2>&1; then \
		ln -sf "$(DOCS_OUT)" "$(DOCS_ROOT)"; \
	else \
		cp "$(DOCS_OUT)" "$(DOCS_ROOT)"; \
	fi

# docs:
# 	@echo "==> Generating Doxygen docs..."
# 	$(DOXYGEN) Doxyfile
# 	@echo "==> Docs at $(DOCS_OUT)"

open-docs: docs
	$(DOCS_OPEN_MSG)
	@if command -v xdg-open >/dev/null 2>&1; then \
		xdg-open "$(DOCS_OUT)"; \
	elif command -v open >/dev/null 2>&1; then \
		open "$(DOCS_OUT)"; \
	elif command -v start >/dev/null 2>&1; then \
		start "$(DOCS_OUT)"; \
	else \
		echo "Please open $(DOCS_OUT) in your browser."; \
	fi

clean-docs:  ## Remove generated doc files in docs/
	$(DOCS_RM_MSG)
	@rm -rf docs
	@rm -f $(DOCS_ROOT)
# ============================================================================ #
#                              STATIC ANALYSIS                                 #
# ============================================================================ #

CPPCHECK_FLAGS :=	--enable=all --inconclusive --quiet $(INCLUDES) \
					-I/usr/include/criterion --suppress=unusedFunction
CPPCHECK_FLAGS += 	--suppress=missingIncludeSystem

static_analysis: ## Run cppcheck on sources
	@command -v cppcheck >/dev/null 2>&1 || { \
		echo "$(RED)cppcheck not found. Install it or disable static_analysis.$(RESET)"; \
		exit 1; }
	$(CPPCHECK_MSG)
	@cppcheck $(CPPCHECK_FLAGS) $(SRCS)


# ============================================================================ #
#                                NORMINETTE                                    #
# ============================================================================ #
norm: ## Run norminette on src/ and inc/
	@echo "$(YELLOW)Running norminette on src/ and inc/...$(RESET)"
	@norminette $(SRC_DIR) $(INC_DIR) | sed 's/^/  /'


config: ## Show current build configuration
	@echo "NAME      = $(NAME)"
	@echo "CC        = $(CC)"
	@echo "CFLAGS    = $(CFLAGS)"
	@echo "LDFLAGS   = $(LDFLAGS)"
	@echo "DEBUG     = $(DEBUG)"
	@echo "SAN       = $(SAN)"
	@echo "COVERAGE  = $(COVERAGE)"

# add stop if any of them fail - now continuuing
check: ## Run norm, static_analysis, build and tests
	@$(MAKE) norm
	@$(MAKE) static_analysis
	@$(MAKE) all
	@$(MAKE) test
	@echo "$(GREEN)[$(OK_ICON)] Full check passed.$(RESET)"

# Default target
# .DEFAULT_GOAL := help
help: ## Show this help
	@echo "$(BOLD)Available targets:$(RESET)"
	@grep -E '^[a-zA-Z0-9_-]+:.*##' $(MAKEFILE_LIST) | \
		sed -e 's/:.*##/: /' | \
		awk 'BEGIN {FS = ":[ ]"} {printf "  $(CYAN)%-18s$(RESET) %s\n", $$1, $$2}'


.PHONY: all clean fclean re aclean \
		test test-vlg test-leak test-log test-clean \
		docs open-docs clean-docs \
		static_analysis norm config help check

#make --trace