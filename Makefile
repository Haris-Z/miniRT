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
CFLAGS      	:= -Wall -Wextra -Werror -Wno-unused-function
CPPFLAGS		:=
CPPCHECK_FLAGS	:=

# LDFLAGS for options passed to the linker step
# (when object files are turned into an executable or shared library).
LDFLAGS     	:=

INCLUDES		=	-Iinc \
					-Ilibs/libft/inc \
					-Ilibs/minilibx-linux

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
	DEBUG_STR := ON
else
	DEBUG_STR := OFF
endif

ifeq ($(SAN),1)
	CFLAGS  += -fsanitize=address,undefined -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
	SAN_STR := ON
else
	SAN_STR := OFF
endif
MODE_MSG = @echo "$(GRAY)[mode] DEBUG=$(DEBUG_STR) SAN=$(SAN_STR) CFLAGS='$(CFLAGS)'$(RESET)"

# ============================================================================ #
#                             PROJECT LAYOUT                                   #
# ============================================================================ #

# Location of sources files
SRC_DIR     	:= src
OBJ_DIR     	:= obj
INC_DIR    		:= inc
# Location of test files
TEST_DIR    	:= tests
LIBS_INC_DIR	:= libs

# Includes
# -L. -lft

MLX_DIR		= #libs/minilibx-linux
MLX_LIB		= #$(MLX_DIR)/libmlx.a
MLX_LDFLAGS	= -lmlx -lXext -lX11 -lm

LIBFT_DIR	= $(LIBS_INC_DIR)/libft
LIBFT		= $(LIBFT_DIR)/libft.a



# ============================================================================ #
#  SOURCE LIST (norm compliant)                                                #
# ============================================================================ #

SRCS		= \
			src/main.c \
			src/error/rt_error.c

# 			src/app/rt_app.c \.
# 			src/app/rt_events.c \.

# 			src/mlx/rt_img.c \.

# 			src/math/vec3_make.c \.
# 			src/math/vec3_ops.c \.
# 			src/math/vec3_norm.c \.
# 			src/math/ray.c \.
# 			src/math/color.c \.

# 			src/scene/world.c \.
# 			src/scene/world_set.c \.
# 			src/scene/world_add.c \.

# 			src/parser/rt_readline.c \.
# 			src/parser/rt_pstr.c \.
# 			src/parser/rt_parse_utils.c \.
# 			src/parser/rt_parse_elems.c \.
# 			src/parser/rt_parse_objs.c \.
# 			src/parser/rt_parser.c \.
# 			src/parser/rt_split_ws.c \.
# 			src/parser/rt_num.c \.

# 			src/camera/cam_build.c \.
# 			src/camera/cam_ray.c \.

# 			src/render/render_smoke.c \.
# 			src/render/hit_utils.c \.
# 			src/render/hit_sphere.c \.
# 			src/render/hit_plane.c \.
# 			src/render/hit_cylinder.c \.
# 			src/render/world_hit.c

#			src/parser/rt_pstr.c \/
#			src/parser/rt_vec_color.c \/
#			src/parser/rt_parse_elems.c \/
#			src/parser/rt_parse_objs.c \/
#			src/parser/rt_parser.c

OBJDIR		= obj
OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

# ============================================================================ #
#                                  RULES                                       #
# ============================================================================ #
all: $(NAME)

# if mlx sources in libs/
# $(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LIBFT) $(MLX_LDFLAGS) -o $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LIBFT) -L/usr/lib $(MLX_LDFLAGS) -o $(NAME)

# if mlx sources in libs/
# $(MLX_LIB):
# 	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I/usr/include $(INCLUDES) -c $< -o $@
# $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean
# $(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
