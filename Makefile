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

#============================RULES============================#

all: libft mlx $(NAME)

libft:
	$(MAKE_NO_PRINT) -C $(LIBFT_PATH)

mlx:
	@cmake $(LIB_MLX_PATH) -B $(LIB_MLX_PATH)/build
	@make -C $(LIB_MLX_PATH)/build -j4

%.o: %.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CC_FLAGS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIB_MLX_PATH)/build
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all libft mlx clean fclean re
