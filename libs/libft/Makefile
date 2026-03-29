# **************************************************************************** #
#                                   libft                                      #
# **************************************************************************** #
GRAY		:= \033[0;90m
CYAN		:= \033[0;36m
BOLD		:= \033[1m
RESET		:= \033[0m
# ============================================================================ #
#   LIBRARY NAME / PRIMARY TARGET                                              #
# ============================================================================ #
NAME        := libft.a
# ============================================================================ #
#   COMPILER & COMPILER FLAGS                                                  #
# ============================================================================ #
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:=
LDFLAGS		:=
LDLIBS		:=
DEPFLAGS	:= -MMD -MP
# ============================================================================ #
#   DEBUG FLAGS                                                                #
# ============================================================================ #

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
DEBUG	?= 1
DEBUG_STR = OFF
SAN		?= 0
SAN_STR := OFF

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -O0
	DEBUG_STR := ON
endif
ifeq ($(SAN),1)
	CFLAGS  += -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
	SAN_STR := ON
endif
define MODE_MSG
	@echo "$(GRAY)[libft mode]$(RESET)"
	@echo "$(GRAY)DEBUG=$(DEBUG_STR)$(RESET)"
	@echo "$(GRAY)SAN=$(SAN_STR)$(RESET)"
	@echo "$(GRAY)CFLAGS='$(CFLAGS)'$(RESET)"
endef

# ============================================================================ #
#   ARCHIVER / INDEXER (for .a files)                                          #
# ============================================================================ #
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
SRC_DIR   := src
OBJ_DIR   := obj
INC_DIR   := inc

CPPFLAGS += -I$(INC_DIR)
# ============================================================================ #
#  SOURCE LIST                                                                 #
# ============================================================================ #
CTYPE := \
	ctype/ft_isalnum.c \
	ctype/ft_isalpha.c \
	ctype/ft_isascii.c \
	ctype/ft_isblank.c \
	ctype/ft_iscntrl.c \
	ctype/ft_isdigit.c \
	ctype/ft_isgraph.c \
	ctype/ft_islower.c \
	ctype/ft_isprint.c \
	ctype/ft_ispunct.c \
	ctype/ft_isspace.c \
	ctype/ft_isupper.c \
	ctype/ft_isxdigit.c \
	ctype/ft_tolower.c \
	ctype/ft_toupper.c

MEM := \
	mem_/ft_bzero.c \
	mem_/ft_memchr.c \
	mem_/ft_memcmp.c \
	mem_/ft_memcpy.c \
	mem_/ft_memmove.c \
	mem_/ft_memset.c

STRING := \
	string/ft_strisws.c \
	string/ft_strchr.c \
	string/ft_strdup.c \
	string/ft_striteri.c \
	string/ft_strjoin.c \
	string/ft_strlcat.c \
	string/ft_strlcpy.c \
	string/ft_strlen.c \
	string/ft_strmapi.c \
	string/ft_strncmp.c \
	string/ft_strndup.c \
	string/ft_strnstr.c \
	string/ft_strrchr.c \
	string/ft_strtrim.c \
	string/ft_substr.c

UTILS := \
	utils/free_mem.c \
	utils/ft_atoi.c \
	utils/ft_atol.c \
	utils/ft_calloc.c \
	utils/ft_free_and_null.c \
	utils/ft_itoa.c \
	utils/ft_realloc.c \
	utils/ft_split.c \
	utils/ft_splitws.c \
	utils/ft_strtoi.c \
	utils/ft_strtod.c

PUT := \
	put_/ft_putchar_fd.c \
	put_/ft_putendl_fd.c \
	put_/ft_putnbr_fd.c \
	put_/ft_putstr_fd.c

LIST := \
	list/ft_lstadd_back.c \
	list/ft_lstadd_front.c \
	list/ft_lstclear.c \
	list/ft_lstdelone.c \
	list/ft_lstiter.c \
	list/ft_lstlast.c \
	list/ft_lstmap.c \
	list/ft_lstnew.c \
	list/ft_lstsize.c

GNL := \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

ERROR := \
	error/errors.c

SRCS_REL := \
	$(CTYPE) \
	$(MEM) \
	$(STRING) \
	$(UTILS) \
	$(PUT) \
	$(LIST) \
	$(GNL) \
	$(ERROR)

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS_REL))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# ============================================================================ #
#                                  RULES                                       #
# ============================================================================ #
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)
	$(MODE_MSG)
# ============================================================================ #
# Compile each .c to its corresponding .o (objects live next to sources)
# ============================================================================ #
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(DEPFLAGS) -c $< -o $@
# ============================================================================ #
#                              CLEAN OBJECT FILES                              #
# ============================================================================ #
clean: ## Remove object files and obj/ directory
	@rm -rf $(OBJ_DIR)
# ============================================================================ #
#                              CLEAN ARCHIVE FILE                              #
# ============================================================================ #
fclean: clean
	@rm -f $(NAME)
	@rm -f $(TEST_BIN)
# ============================================================================ #
#                           FULL REBUILD (CLEAN + ALL)                         #
# ============================================================================ #
re: fclean all
# ============================================================================ #
#                                TEST TARGETS                                  #
# ============================================================================ #

# Default target
# .DEFAULT_GOAL := help
help: ## Show this help
	@echo "$(BOLD)Available targets:$(RESET)"
	@grep -E '^[a-zA-Z0-9_-]+:.*##' $(MAKEFILE_LIST) | \
		sed -e 's/:.*##/: /' | \
		awk 'BEGIN {FS = ":[ ]"} {printf "  $(CYAN)%-18s$(RESET) %s\n", $$1, $$2}'

-include $(DEPS)

.PHONY:	all clean fclean re \
		help

#make --trace