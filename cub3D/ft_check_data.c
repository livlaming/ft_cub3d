/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/07 18:00:47 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		ft_check_textures(t_mega *mega)
{
	int		dir;
	size_t	start;
	size_t	end;
	char	*temp;

	temp = NULL;
	dir = 0;
	start = 0;
	end = ft_strlen(mega->tex[dir].texture);
	while (dir < 5)
	{
		end = ft_strlen(mega->tex[dir].texture) - 1;
		while (mega->tex[dir].texture[start] == ' ')
			start++;
		while (mega->tex[dir].texture[end] == ' ' && end > 0)
			end--;
		temp = ft_substr(mega->tex[dir].texture, start, (end - start + 1));
		free(mega->tex[dir].texture);
		mega->tex[dir].texture = ft_strdup(temp);
		free(temp);
		temp = NULL;
		start = 0;
		dir++;
	}
}

static void		ft_check_screensize(t_mega *mega, int screen_w, int screen_h)
{
	mlx_get_screen_size(&mega->win, &screen_w, &screen_h);
	if (mega->parser.screenshot == 0 && screen_h < mega->win.screen_h)
	{
		mega->win.screen_w =
			mega->win.screen_w / ((float)mega->win.screen_h / (float)screen_h);
		mega->win.screen_h = screen_h;
	}
	if (mega->parser.screenshot == 0 && screen_w < mega->win.screen_w)
	{
		mega->win.screen_h =
			mega->win.screen_h / ((float)mega->win.screen_w / (float)screen_w);
		mega->win.screen_w = screen_w;
	}
	if (mega->win.screen_h <= 0 || mega->win.screen_w <= 0)
		ft_error_message(21);
}

static int		ft_check_resolution(t_mega *mega, int start)
{
	while (mega->parser.res[start] == ' ')
		start++;
	mega->win.screen_w = ft_atoi(&mega->parser.res[start]);
	while (ft_isdigit(mega->parser.res[start]) == 1)
		start++;
	while (mega->parser.res[start] == ' ')
		start++;
	mega->win.screen_h = ft_atoi(&mega->parser.res[start]);
	while (ft_isdigit(mega->parser.res[start]) == 1)
		start++;
	while (mega->parser.res[start] != '\0')
	{
		if (mega->parser.res[start] != ' ')
			ft_error_message(0);
		start++;
	}
	if (mega->win.screen_w <= 0 || mega->win.screen_h <= 0)
		ft_error_message(0);
	ft_check_screensize(mega, 0, 0);
	return (0);
}

static int		ft_calc_sprites(t_mega *mega, size_t x, size_t y, size_t s)
{
	if (mega->sp.numb_sprites > 0)
	{
		free(mega->sp.sprites);
		mega->sp.sprites =
			malloc(sizeof(t_sprite) * ((size_t)(mega->sp.numb_sprites + 1)));
		if (!mega->sp.sprites)
			return (-1);
		while (y < mega->parser.ycounter)
		{
			while (mega->win.map[y][x] != '\0')
			{
				if (mega->win.map[y][x] == '2')
				{
					mega->sp.sprites[s].x = (double)x + 0.5;
					mega->sp.sprites[s].y = (double)y + 0.5;
					s++;
				}
				x++;
			}
			x = 0;
			y++;
		}
	}
	return (0);
}

int				ft_check_data(t_mega *mega)
{
	if (mega->ray.posx < 1 || mega->parser.dir_check != 1)
	{
		write(1, "Error\nInvalid map -> ", 21);
		write(1, "The starting position of the player is missing\n", 47);
		return (-1);
	}
	if (mega->tex[NO].texture == NULL || mega->tex[SO].texture == NULL ||
			mega->tex[EA].texture == NULL || mega->tex[WE].texture == NULL ||
				mega->tex[SP].texture == NULL || mega->parser.floor == NULL ||
					mega->parser.ceiling == NULL || mega->parser.res == NULL)
	{
		write(1, "Error\nInvalid map -> Missing input\n", 35);
		return (-1);
	}
	ft_check_textures(mega);
	mega->parser.floor_col = ft_check_rgb(mega, mega->parser.floor, -1, -1);
	mega->parser.ceiling_col = ft_check_rgb(mega, mega->parser.ceiling, -1, -1);
	if (mega->win.map_w * (int)mega->parser.ycounter >= 117900)
		ft_error_message(20);
	if (flood_fill(mega->ray.posx, mega->ray.posy, '3', mega) == -1)
		ft_error_message(10);
	ft_check_resolution(mega, 0);
	if (ft_calc_sprites(mega, 0, 0, 0) == -1)
		return (-1);
	return (0);
}
