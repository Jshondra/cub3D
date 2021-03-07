# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jshondra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 15:16:08 by jshondra          #+#    #+#              #
#    Updated: 2020/11/06 14:35:56 by jshondra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror 

#SRCDIR = gnl/

SRCS = *.c \
	./gnl/*.c \
	./libft/*.c\

HEAD = cub3D.h

FLAG_MLX = -framework OpenGL -framework AppKit libmlx.dylib


# OBJSBONUS = $(BONUS:.c=.o)

# OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): 
		gcc $(CFLAGS) $(SRCS) $(FLAG_MLX) -c -o $(NAME)

# %.o: %.c $(HEAD)
# 	gcc $(CFLAGS) $(SRCS) $(FLAG_MLX) -c -o $(NAME)

clean:
	rm -rf *.o

fclean: 
	rm -rf $(NAME)

re: clean fclean all

.PHONY: all  clean fclean re bonus

