ESC   := \033
GRAY  := $(ESC)[0;90m
RESET := $(ESC)[0m

# ============================================================================ #
#                                   miniRT                                     #
# ============================================================================ #
NAME = miniRT
# ============================================================================ #
#   COMPILE FLAGS                                                              #
# ============================================================================ #
CC				:= cc
# CFLAGS → compile flags (-Wall ..., -Iinclude, -g, etc.)
CFLAGS			:= -Wall -Wextra -Werror \
				-Wno-unused-function -Wdouble-promotion
# CPPFLAGS  -> preprocessor flags ( -I..., -D... )
CPPFLAGS		:=
# LDFLAGS → link flags for paths/options (-L..., -Wl,...)
LDFLAGS     	:=
# LDLIBS (or LIBS) → the libraries (-lft -lm ...)
LDLIBS			:=
DEPFLAGS	:= -MMD -MP
# ============================================================================ #
#   COMPILER PRE-PROCESSOR OPTIONS                                             #
# ============================================================================ #
# Example for adding more flags
# CPPFLAGS    :=
# ifeq ($(LEAK_TEST),1) - for testing
# 	CPPFLAGS += -DLEAK_TEST
# endif
# Debug & sanitizer toggles
# Usage:
#   make DEBUG=1        → adds -g3 -O0
#   make SAN=1          → adds -fsanitize=address (compile + link)
#   make DEBUG=1 SAN=1  → both
DEBUG	?= 1
PROFILER ?= 0
SAN		?= 1

DEBUG_STR = OFF
SAN_STR := OFF

ifeq ($(DEBUG),1)
	CFLAGS += -ggdb3 -O0
	DEBUG_STR := ON
endif
ifeq ($(SAN),1)
	CFLAGS  += -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
	SAN_STR := ON
endif
ifeq ($(PROFILER),1)
	CFLAGS += -pg
	LDFLAGS += -pg
endif

define MODE_MSG
	@echo "$(GRAY)[miniRT mode]$(RESET)"
	@echo "$(GRAY)DEBUG=$(DEBUG_STR)$(RESET)"
	@echo "$(GRAY)SAN=$(SAN_STR)$(RESET)"
	@echo "$(GRAY)CFLAGS='$(CFLAGS)'$(RESET)"
	@echo "$(GRAY)LDFLAGS='$(LDFLAGS)'$(RESET)"
	@echo "$(GRAY)LDLIBS='$(LDLIBS)'$(RESET)"
endef

# ============================================================================ #
#                             PROJECT LAYOUT                                   #
# ============================================================================ #
# Location of sources files
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR    	:= inc
LIBS_DIR	:= libs
# Location of test files
TEST_DIR    := tests
TEST_FILES	:= tests/test_files
DEFAULT_TEST:= $(TEST_FILES)/mini_field.rt
# ============================================================================ #
LIBFT_DIR	:= $(LIBS_DIR)/libft
#MLX_DIR		:= $(LIBS_DIR)/minilibx-linux
LIBFT		= $(LIBFT_DIR)/libft.a
#MLX			= $(MLX_DIR)/libmlx.a
# ============================================================================ #
# include dirs -> CPPFLAGS (-I...)
INC_DIRS  := $(INC_DIR)/ $(LIBFT_DIR)/inc
CPPFLAGS  += $(addprefix -I,$(INC_DIRS))
# ============================================================================ #
# library dirs -> LDFLAGS (-L...)
# LIB_DIRS  := $(LIBFT_DIR) $(MLX_DIR)
LIB_DIRS  := $(LIBFT_DIR)
LDFLAGS   += $(addprefix -L,$(LIB_DIRS))
# ============================================================================ #
# libraries -> LDLIBS (-l...)
LDLIBS    += -lft -lmlx -lXext -lX11 -lm

# ============================================================================ #

# ============================================================================ #
#  SOURCE LIST                                                                 #
# ============================================================================ #

COLOR := \
		color/color.c \
		color/shader.c \
		color/shader_utils.c

B_COLOR := \
		color/color.c \
		color/shader_bonus.c \
		color/shader_utils.c 

ERROR := \
		error/rt_error.c

PARSE := \
		parse/parse_file.c \
		parse/parse_elem.c \
		parse/parse_obj.c \
		parse/parse_utils.c \
		parse/file_open.c

RENDER := \
		render/intersections.c \
		render/hit_cy.c \
		render/cy_utils.c \
		render/hit_utils.c \
		render/viewport.c \
		render/rays.c

B_RENDER := \
		render/intersections.c \
		render/hit_cy.c \
		render/cy_utils.c \
		render/hit_utils.c \
		render/viewport_bonus.c \
		render/rays_bonus.c

RT := \
		rt/rt_events.c \
		rt/rt_img.c \
		rt/rt_init.c \
		rt/rt_run.c

SCENE := \
		scene/scene_add_obj.c \
		scene/scene_init.c \
		scene/scene_set_elem.c

VEC := \
		vec/vec.c \
		vec/vec_basic_ops.c \
		vec/vec_norm.c \
		vec/vec_ops.c \
		vec/vec_utils.c \
		vec/mat_ops.c

PPM := \
		write_to_ppm/save_ppm.c

DPRINTS := \
			debug/prints.c \
			debug/print_scene.c

SRCS := \
		test_main.c \
		$(DPRINTS) \
		$(COLOR) \
		$(ERROR) \
		$(PARSE) \
		$(RENDER) \
		$(RT) \
		$(PPM) \
		$(VEC) \
		$(SCENE)

B_SRCS := \
		test_main.c \
		$(DPRINTS) \
		$(B_COLOR) \
		$(ERROR) \
		$(PARSE) \
		$(B_RENDER) \
		$(RT) \
		$(PPM) \
		$(VEC) \
		$(SCENE)

# ============================================================================ #
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
# ============================================================================ #
# ============================================================================ #
B_SRCS := $(addprefix $(SRC_DIR)/,$(B_SRCS))
B_OBJS := $(B_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
B_DEPS := $(B_OBJS:.o=.d)
# ============================================================================ #

# ============================================================================ #
all: $(NAME)
# ============================================================================ #

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME) 
	$(MODE_MSG)
# ============================================================================ #

bonus:	CFLAGS += -DMAX_LIGHTS=5
bonus:	$(LIBFT) $(B_OBJS)
	@$(CC) $(CFLAGS) $(B_OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME) 
	$(MODE_MSG)

# ============================================================================ #
# if mlx sources in libs - has to compile per subject
# $(MLX_LIB):
# 	$(MAKE) -C $(MLX_DIR)
$(LIBFT):
	@echo "Compiling libft .."
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) \
	SAN=$(SAN) DEBUG=$(DEBUG)
# ============================================================================ #
# compile .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(DEPFLAGS) $(CFLAGS) -c $< -o $@
	@echo "[miniRT] compiled. $<"
# ============================================================================ #

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

# runs with tui
# bminirt are breakpoints set in gdbinit
# to load gdbinit  - ex " source .gdbinit"
debug: fclean ## run gdb
	@$(MAKE) --no-print-directory DEBUG=1 SAN=0
	@echo "Starting GDB with $(NAME) $(DEFAULT_TEST)"
	@gdb -tui -q \
	-ex "source .gdbinit" \
	-ex "bminirt" \
	-ex "layout src" \
	-ex "focus cmd" \
	-ex "refresh" \
	-ex "run $(DEFAULT_TEST)" \
	./$(NAME)
#@gdb -q -ex "source .gdbinit" -ex "bminirt" -ex "run $(TEST_DIR)/test_files/mini.rt" miniRT

# run: $(NAME)
# 	./$(NAME) $(TEST_FILES)

# run: $(NAME)
# 	@echo "$(YELLOW)Running quick test ... $(RESET)"

# valgrind: $(NAME)
# 	valgrind \
# 	--leak-check=full \
# 	--show-leak-kinds=all \
# 	--track-origins=yes \
# 	./$(NAME) $(TEST_FILES)/mandatory.rt

# ============================================================================ #

test: $(NAME) ## run with mini_field.rt for testing
	@echo "$(YELLOW) Runnning test ... $(RESET)"
	./$(NAME) $(DEFAULT_TEST)

TEST_P = tst_rtparse

$(TEST_P): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) \
	tests/parse/test_parser.c \
	$(filter-out $(OBJ_DIR)/main.o, $(OBJS)) \
	$(LDLIBS) $(LDFLAGS) \
	$(LIBFT) -o \
	$(TEST_P)

test_parse: $(TEST_P)
	./$(TEST_P) tests/test_files/scenes/03_basic.rt

test_errors: ## run tests on error files
	@echo "TESTING ERROR FILES"
	@./$(TEST_P) tests/test_files/error_scene/06_only_white.rt
	@./$(TEST_P) tests/test_files/error_scene/01_duplicate_A.rt
	@./$(TEST_P) tests/test_files/error_scene/01_duplicate_C.rt
	@./$(TEST_P) tests/test_files/error_scene/01_duplicate_L.rt
	@./$(TEST_P) tests/test_files/error_scene/02_missing_A.rt
	@./$(TEST_P) tests/test_files/error_scene/02_missing_C.rt
	@./$(TEST_P) tests/test_files/error_scene/02_missing_L.rt
	@./$(TEST_P) tests/test_files/error_scene/03_empty_after_A.rt
	@./$(TEST_P) tests/test_files/error_scene/03_error_trailing_garbage.rt
	@./$(TEST_P) tests/test_files/error_scene/03_missing_color_A.rt
	@./$(TEST_P) tests/test_files/error_scene/03_too_many_toks_A.rt
	@./$(TEST_P) tests/test_files/error_scene/04_invalid_ratio_A.rt
	@./$(TEST_P) tests/test_files/error_scene/04_invalid_ratio_range.rt
	@./$(TEST_P) tests/test_files/error_scene/05_invalid_vec_C.rt
	@./$(TEST_P) tests/test_files/error_scene/err_invalid_delim.rt
	@./$(TEST_P) tests/test_files/error_scene/err_invalid_id.rt
	@./$(TEST_P) tests/test_files/error_scene/err_invalid_no_ext
	@./$(TEST_P) tests/test_files/error_scene/err_invalid_param.rt
	@./$(TEST_P) tests/test_files/error_scene/err_unused_param.rt
	@./$(TEST_P) tests/test_files/error_scene/warn_fov_range.rt

# ============================================================================ #

prof: fclean ## Compile with -pg and run gprof
	@$(MAKE) --no-print-directory PROFILER=1 DEBUG=1 SAN=0
	@echo "Running miniRT with profiling..."
	@./$(NAME) $(DEFAULT_TEST)
	@echo "Generating gprof report..."
	@gprof $(NAME) gmon.out > gprof_report.txt
	@echo "Report saved to gprof_report.txt"

prof_b: fclean ## Compile with -pg and run gprof
	@make bonus --no-print-directory PROFILER=1 DEBUG=1 SAN=0
	@echo "Running miniRT with profiling..."
	@./$(NAME) $(DEFAULT_TEST)
	@echo "Generating gprof report..."
	@gprof $(NAME) gmon.out > gprof_report.txt
	@echo "Report saved to gprof_report.txt"
# ============================================================================ #

# ============================================================================ #
help: ## Show this help
	@echo "$(BOLD)Available targets:$(RESET)"
	@grep -E '^[a-zA-Z0-9_-]+:.*##' $(MAKEFILE_LIST) | \
		sed -e 's/:.*##/: /' | \
		awk 'BEGIN {FS = ":[ ]"} {printf "  $(CYAN)%-18s$(RESET) %s\n", $$1, $$2}'
# ============================================================================ #

-include $(DEPS) $(B_DEPS)

.PHONY: all clean fclean re \
		debug \
		test \
		help \
		test_parse \
		test_errors
