# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <lisa@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/06 08:42:14 by livlamin      #+#    #+#                  #
#    Updated: 2020/10/23 19:28:21 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft/libft.a

MLX = libmlx.dylib

SRC = main.c \
		ft_cub.c \
		ft_calc_walls.c \
		ft_keys_put_close.c \
		ft_textures.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_set_start_pos.c \
		ft_set_start_pos_sp.c \
		ft_error_message.c \
		ft_check_data.c \
		ft_check_rgb.c \
		ft_read_cubfile.c \
		ft_floodfill.c \
		ft_save_map.c \
		ft_create_sprites.c \
		ft_calc_dist_sprite.c \
		ft_movement.c \
		ft_raycast.c \
		ft_make_screenshot.c \
		ft_create_map.c
		
OBJ = $(addprefix objects/, $(SRC:.c=.o))

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ) cub.h
	$(CC) -L. -Llibft -lmlx -lft -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)

$(LIBFT):
	$(MAKE) -C $(dir $(LIBFT)) all

$(MLX):
	$(MAKE) -C mlx all
	ln -sf mlx/$(MLX) $(MLX)

objects/%.o: %.c
	$(shell mkdir -p $(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(dir $(LIBFT)) clean
	$(MAKE) -C mlx clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(dir $(LIBFT)) fclean
	$(RM) libmlx.dylib
	$(shell rmdir objects)

bonus: re

re:	fclean all

.PHONY: clean fclean