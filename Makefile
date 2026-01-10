# Colors for nicer output
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

# **************************************************************************** #
#                                   miniRT                                     #
# **************************************************************************** #

# Program name 
NAME 		= miniRT

# ============================================================================ #
#   COMPILE FLAGS                                                              #
# ============================================================================ #

CC          	:= cc
# CFLAGS → compile flags (-Wall ..., -Iinclude, -g, etc.)
CFLAGS      	:= -Wall -Wextra -Werror -Wno-unused-function
# -Wdouble-promotion
# CPPFLAGS  -> preprocessor flags ( -I..., -D... )
CPPFLAGS		:=
# LDFLAGS → link flags for paths/options (-L..., -Wl,...)
LDFLAGS     	:=
# LDLIBS (or LIBS) → the libraries (-lft -lm ...)
LDLIBS			:=

# ============================================================================ #
#   COMPILER PRE-PROCESSOR OPTIONS                                             #
# ============================================================================ #
# Example
# CPPFLAGS    :=
# ifeq ($(LEAK_TEST),1) - for testing
# 	CPPFLAGS += -DLEAK_TEST
# endif
# Debug & sanitizer toggles
# Usage:
#   make DEBUG=1        → adds -g3 -O0
#   make SAN=1          → adds -fsanitize=address (compile + link)
#   make DEBUG=1 SAN=1  → both
V 			?= 1
DEBUG		?= 0
RT_DEBUG	?= 1
SAN			?= 1
DEBUG_STR 	?= 
SAN_STR 	?= 

ifeq ($(DEBUG),1)
	CFLAGS += -ggdb3 -O0
	DEBUG_STR := ON
else
	DEBUG_STR := OFF
endif

ifeq ($(SAN),1)
	CFLAGS  += -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
	SAN_STR := ON
else
	SAN_STR := OFF
endif

ifeq ($(RT_DEBUG),1)
	CPPFLAGS += -DRT_DEBUG
endif

MODE_MSG = @echo "$(GRAY)[miniRT mode:] \
					DEBUG='$(DEBUG_STR)' \
					SAN='$(SAN_STR)' \
					CFLAGS='$(CFLAGS)'$(RESET)"

# ============================================================================ #
#                             PROJECT LAYOUT                                   #
# ============================================================================ #

# ============================================================================ #
# Location of sources files
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR    	:= inc
LIBS_DIR	:= libs
# Location of test files
TEST_DIR    := tests
# ============================================================================ #
LIBFT_DIR	:= $(LIBS_DIR)/libft
#MLX_DIR		:= $(LIBS_DIR)/minilibx-linux
LIBFT		= $(LIBFT_DIR)/libft.a
#MLX			= $(MLX_DIR)/libmlx.a
# ============================================================================ #

# if mlx in libs/
# INC_DIRS  := $(INC_DIR) $(LIBFT_DIR)/inc $(MLX_DIR)
# ============================================================================ #
# include dirs -> CPPFLAGS (-I...)
INC_DIRS  := $(INC_DIR) $(LIBFT_DIR)/inc
CPPFLAGS  += $(addprefix -I,$(INC_DIRS))
# ============================================================================ #
# library dirs -> LDFLAGS (-L...)
# LIB_DIRS  := $(LIBFT_DIR) $(MLX_DIR)
LIB_DIRS  := $(LIBFT_DIR)
LDFLAGS   += $(addprefix -L,$(LIB_DIRS))
# ============================================================================ #
# libraries -> LDLIBS (-l...)
LDLIBS    += -lft -lmlx -lXext -lX11 -lm -lz
# ============================================================================ #

# ============================================================================ #
#  SOURCE LIST                                                                 #
# ============================================================================ #

# ============================================================================ #
SRCS		:= \
			main.c \
			error/rt_error.c \
			rt/rt_run.c \
			rt/rt_init.c \
			rt/rt_img.c \
			rt/rt_events.c \
			color/color.c \
			parse/parse_amb.c \
			parse/parse_cam.c \
			parse/parse_elems.c \
			parse/parse_light.c \
			parse/parse_num.c \
			parse/parse_obj.c \
			parse/parse_file.c \
			parse/parse_utils.c \
			parse/parse_vec.c \
			scene/scene_add_obj.c \
			scene/scene_init.c \
			scene/scene_set_elem.c \
			vec/vec_len.c \
			vec/vec_norm.c \
			vec/vec_ops.c \
			vec/vec_ops1.c \
			vec/vec.c \
			log/rt_log.c \
			log/dbg_log.c \
			log/trace_log.c
			
#			ray/ray.c

# ============================================================================ #
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# ============================================================================ #

# ============================================================================ #
#                                  RULES                                       #
# ============================================================================ #

# ============================================================================ #
all: $(NAME)
# ============================================================================ #
# if mlx sources in libs/
# $(NAME): $(OBJS) $(LIBFT) $(MLX)
# 	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# if mlx installed on system
# Link: .o -> + libs -> executable
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(GREEN)[$(OK_ICON) ] [miniRT] Build succeeded $(RESET) → $(BOLD)$(NAME)$(RESET)"
	$(MODE_MSG)
# ============================================================================ #
# if mlx sources in libs - has to compile per subject
# $(MLX_LIB):
# 	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	@echo "$(GREEN)[$(OK_ICON) ] [miniRT] Compiling libft .. $(RESET)$(BOLD)$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) SAN=$(SAN) DEBUG=$(DEBUG) V=$(V)
# ============================================================================ #
# compile .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@echo "$(CYAN)[$(BUILD_ICON)] [miniRT] Compiled →$(RESET) $<"
# ============================================================================ #

clean:
	@echo "$(RED)[$(WARN_ICON)] [miniRT] Deleting object files ...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)[$(ERR_ICON)] [miniRT] Object files removed .$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
# $(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)[$(WARN_ICON)] [miniRT] Deleting exectuable ...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)[$(ERR_ICON)] [miniRT] Executable removed → $(NAME).$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
	@echo "$(BLUE)[$(WARN_ICON)] [miniRT] Rebuilt..  → $(RESET) $(NAME) "

# delete all generated files
aclean: fclean clean-docs

# ============================================================================ #

# run: $(NAME)
# 	$(SRCS) += main.c
# 	@echo "$(YELLOW)Running quick test ... $(RESET)"
# 	./$(NAME) main.c $(TEST_DIR)/test_scenes/scenes/mini.rt

test: $(NAME)
	@echo "$(YELLOW) Runnning test ... $(RESET)"
	./$(NAME) $(TEST_DIR)/test_files/mini.rt

# fsan:

# vlg:

# ============================================================================ #
#                           DOCUMENTATION (Doxygen)                            #
# ============================================================================ #

# ============================================================================ #
# Docs-related messages
DOCS_GEN_MSG  = @echo "$(MAGENTA)[$(DOC_ICON)] Generating Doxygen docs...$(RESET)"
DOCS_AT_MSG   = @echo "$(MAGENTA)[$(DOC_ICON)] Docs at $(DOCS_OUT)$(RESET)"
DOCS_OPEN_MSG = @echo "$(MAGENTA)[$(DOC_ICON)] Opening docs...$(RESET)"
DOCS_RM_MSG   = @echo "$(MAGENTA)[$(DOC_ICON)] Removing generated docs...$(RESET)"
# ============================================================================ #
DOXYGEN		?= doxygen
DOCS_OUT	:= docs/html/index.html
DOCS_ROOT	:= index.html
# ============================================================================ #
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
# ============================================================================ #
# docs:
# 	@echo "==> Generating Doxygen docs..."
# 	$(DOXYGEN) Doxyfile
# 	@echo "==> Docs at $(DOCS_OUT)"
# ============================================================================ #
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
# ============================================================================ #
clean-docs:  ## Remove generated doc files in docs/
	$(DOCS_RM_MSG)
	@rm -rf docs
	@rm -f $(DOCS_ROOT)
# ============================================================================ #


# ============================================================================ #
#                              STATIC ANALYSIS                                 #
# ============================================================================ #
# cppcheck
CPPCHECK          ?= cppcheck
CPPCHECK_REPORT   ?= cppcheck_report.txt
# ============================================================================ #
CPPCHECK_MSG      = @echo "$(YELLOW)[$(WARN_ICON)] Running static analysis with cppcheck...$(RESET)"
# pptional
#   make static_analysis CPPCHECK_STRICT=1   -> treat warnings as errors (non-zero exit)
#   make static_analysis CPPCHECK_JOBS=8     -> parallel analysis
CPPCHECK_STRICT   ?= 0
CPPCHECK_JOBS     ?= 0
# ============================================================================ #
# include dirs from the build
CPPCHECK_INCLUDES := $(CPPFLAGS)

# basic flags
CPPCHECK_FLAGS := \
	--enable=warning,style,performance,portability \
	--inconclusive \
	--force \
	--inline-suppr \
	--quiet \
	--suppress=missingIncludeSystem \
	--suppress=unusedFunction
# ============================================================================ #
# all checks --enable=all
# CPPCHECK_FLAGS := $(filter-out --enable=%,$(CPPCHECK_FLAGS)) --enable=all
ifneq ($(CPPCHECK_JOBS),0)
	CPPCHECK_FLAGS += -j $(CPPCHECK_JOBS)
endif

# fail on issue
ifeq ($(CPPCHECK_STRICT),1)
	CPPCHECK_FLAGS += --error-exitcode=1
endif
# ============================================================================ #
static_analysis: ## Run cppcheck on sources
	@command -v $(CPPCHECK) >/dev/null 2>&1 || { \
		echo "$(RED)cppcheck not found. Install it (or disable static_analysis).$(RESET)"; \
		exit 1; \
	}
	$(CPPCHECK_MSG)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPPCHECK_INCLUDES) $(SRCS)

# 	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPPCHECK_INCLUDES) $(SRCS) 2> $(CPPCHECK_REPORT) || true
# 	@echo "$(GRAY)[report] $(CPPCHECK_REPORT)$(RESET)"
# ============================================================================ #

# ============================================================================ #
#                                NORMINETTE                                    #
# ============================================================================ #
# norm: ## Run norminette on src/ and inc/
# 	@echo "$(YELLOW)Running norminette on src/ and inc/...$(RESET)"
# 	@norminette $(SRC_DIR) $(INC_DIR) | sed 's/^/  /'

# ============================================================================ #
#                                                                              #
# ============================================================================ #

config: ## Show current build configuration
	@echo "NAME      = $(NAME)"
	@echo "CC        = $(CC)"
	@echo "CPPFLAGS  = $(CPPFLAGS)"
	@echo "CFLAGS    = $(CFLAGS)"
	@echo "LDFLAGS   = $(LDFLAGS)"
	@echo "LDLIBS    = $(LDLIBS)"
	@echo "DEBUG     := $(DEBUG_STR) | $(DEBUG)"
	@echo "SAN       := $(SAN_STR)	 | $(SAN)"
# ============================================================================ #
help: ## Show this help
	@echo "$(BOLD)Available targets:$(RESET)"
	@grep -E '^[a-zA-Z0-9_-]+:.*##' $(MAKEFILE_LIST) | \
		sed -e 's/:.*##/: /' | \
		awk 'BEGIN {FS = ":[ ]"} {printf "  $(CYAN)%-18s$(RESET) %s\n", $$1, $$2}'
# ============================================================================ #
.PHONY: all clean fclean re aclean \
		docs open-docs clean-docs \
		static_analysis \
		config help \
		test run
