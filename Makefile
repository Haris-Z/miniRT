# **************************************************************************** #
#                                   miniRT                                     #
# **************************************************************************** #

NAME = miniRT

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

# Icons / Emojis for fun
OK_ICON		:= ✔
WARN_ICON	:= ●
ERR_ICON	:= ✗
BUILD_ICON	:= 🔧
DOC_ICON	:= 📚



all: $(NAME)

# CC = cc -Wall -Wextra -Werror 
CC = cc -g

SRC = src/main.c src/camera.c src/rays.c src/vector.c src/error/rt_error.c

OBJ = $(patsubst src/%.c, src/%.o,$(SRC))
RM = rm -rf

#Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m


$(NAME): $(OBJ)
# 	make -C includes
	$(CC) $(OBJ) libs/libft/libft.a -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -I/usr/include -O3 -c $< -o $@

# Clean up object files 
clean:
	@echo "$(BLUE)Cleaning up...$(RESET)"
	$(RM) $(OBJ)
	$(RM) ./obj
	$(RM) make clean includes/*.o
	@echo "$(RED) Object files cleaned.$(NO_COLOR)"

# Clean up everything
fclean: clean
	@echo "$(BLUE) Removing executable...$(RESET)"
	$(RM) $(NAME)
	$(RM) includes/libft.a
	@echo "$(RED) PROJECT cleaned.$(NO_COLOR)"

# Rebuild 
re: fclean all
	@echo "$(BLUE) Rebuilding Project...$(RESET)"

# debug:
# 	make -C includes
# 	$(CC) $(SRC) includes/libft.a -g -lmlx -L/usr/lib -lXext -lX11 -lm -lz 

.PHONY: clean fclean re all debug