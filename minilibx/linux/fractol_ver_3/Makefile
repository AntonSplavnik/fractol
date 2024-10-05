NAME = fractals

SRCS = srcs/main.c srcs/fractals.c srcs/hooks.c srcs/utils.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Iincludes -pthread

MLX = -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)
	@echo "Compiled $(NAME)"

clean:
	@rm -f $(OBJS)
	@echo "Cleaned up object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Removed binary"

re: fclean all
	@echo "Rebuilt project"
