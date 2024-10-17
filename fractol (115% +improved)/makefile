# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 18:46:28 by asplavni          #+#    #+#              #
#    Updated: 2024/10/15 14:46:55 by asplavni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Target executable
NAME        = fractol

# Source files
SRC         = main.c \
              events.c \
              init.c \
              math_utils.c \
              render.c \
              string_utils.c\
			  handle_pixel.c \
			  thread_render.c \
			  render_fractal_progressive.c \

# Object files
OBJ         = $(SRC:.c=.o)

# Header files
HEADERS     = fractol.h

# Library path and options for MiniLibX
MLX_DIR     = ./minilibx-linux
MLX_LIB     = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext

# Rule to compile both the project and MiniLibX
all: $(MLX_DIR)/libmlx_Linux.a $(NAME)

# Rule to link object files and create the executable, including the MLX library
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

# Rule to compile each .c file into .o object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile MiniLibX (assuming it's already downloaded)
$(MLX_DIR)/libmlx_Linux.a:
	make -C $(MLX_DIR)

# Rule to clean up object files
clean:
	rm -f $(OBJ)
	make -C $(MLX_DIR) clean

# Rule to clean up object files and binary
fclean: clean
	rm -f $(NAME)

# Rule to recompile everything from scratch
re: fclean all

# Phony targets to avoid conflicts with files named "all", "clean", etc.
.PHONY: all clean fclean re