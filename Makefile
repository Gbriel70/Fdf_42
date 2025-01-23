#============================FLAGS============================#

NAME = fdf
CC = cc
CC_FLAGS = -Wall -Werror -Wextra -g3
MAKE_NO_PRINT = $(MAKE) --no-print-directory

#============================PATHS============================#

SRCS_PATH = ./src
LIBFT_PATH = ./libs/libft_plus
LIB_MLX_PATH = ./libs/MLX42
HEADERS_PATH = ./includes

#=========================INCLUDES============================#

INCLUDES = -I$(HEADERS_PATH) \
			-I$(LIB_MLX_PATH)/include

#=========================LIBRARIES============================#

LIBFT		=	-L$(LIBFT_PATH) -lft
MLX			=	$(LIB_MLX_PATH)/build/libmlx42.a
MLX_FLAGS	=	-ldl -lglfw -pthread -lm

#============================FILES============================#

SRCS = $(wildcard $(SRCS_PATH)/*.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(HEADERS_PATH)/fdf.h

#============================COLORS============================#

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

#============================RULES=============================#

all: libft mlx $(NAME)
	@echo "$(GREEN)All files are up to date!$(RESET)"

libft:
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	$(MAKE_NO_PRINT) -C $(LIBFT_PATH)

mlx:
	@echo "$(YELLOW)Compiling MLX42...$(RESET)"
	@cmake $(LIB_MLX_PATH) -B $(LIB_MLX_PATH)/build > /dev/null 2>&1
	@make -C $(LIB_MLX_PATH)/build -j4 > /dev/null 2>&1

%.o: %.c $(HEADERS)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	$(CC) $(CC_FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	$(CC) $(OBJS) $(CC_FLAGS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) Build complete!$(RESET)"

-include $(DEPS)

#============================LEAKS============================#

#FILE VARIABLE
FILE ?=

leak: all
	@if [-z "$(FILE)"]; then \
		echo "$(RED)Error: FILE variable is not set. Usage: make leak FILE=<path_to_fdf_file>"; \
		exit 1; \
	fi
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fdf $(FILE)

#============================CLEAN============================#

clean:
	@echo "$(MAGENTA)Cleaning up...$(RESET)"
	@rm -rf $(OBJS)
	@rm -rf $(LIB_MLX_PATH)/build
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@echo "$(MAGENTA)Full clean...$(RESET)"
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all libft mlx clean fclean re
