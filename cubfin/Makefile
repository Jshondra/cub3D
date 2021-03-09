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

GNL =	$(addprefix gnl/, \
		get_next_line.c \
		get_next_line_utils.c )

FUNC =	$(addprefix functions/, \
		cub3d.c\
		draw_wall_sprites.c\
		hooks.c\
		parser.c\
		player_pos.c\
		ray_cast.c\
		utils.c\
		error.c\
		mode_atoi.c\
		player_pars.c\
		print.c\
		screenshot.c\
		utils_for_print.c )

MLX = -lmlx -framework OpenGL -framework AppKit libmlx.dylib

FILE_HEAD = functions/cub3D.h

HEAD =	./libft

HEADERS = $(addprefix -I , $(HEAD))

FLAG_LIBFT = libft.a

all: $(NAME)

$(NAME): $(SRCS) $(FILE_HEAD)
		@$(MAKE) -C libft/
		@$(MAKE) -C mlx/
		mv mlx/libmlx.dylib ./
		mv libft/libft.a ./libft.a
		gcc $(CFLAGS) $(GNL) $(FUNC) $(HEADERS) $(FLAG_LIBFT) $(MLX) -o $(NAME)

clean:
	rm -rf libft/*.o
	rm -rf mlx/*.o
	rm -rf libmlx.dylib
	rm -rf libft.a

fclean: clean
	rm -rf $(NAME)

re: fclean clean all

.PHONY: all clean fclean re
