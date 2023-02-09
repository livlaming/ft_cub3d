/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_keys_put_close.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 12:33:37 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		ft_close_window(t_mega *mega)
{
	if (!mega->parser.screenshot)
		mlx_destroy_window(mega->win.mlx, mega->win.mlx_win);
	exit(0);
	return (0);
}

char	*ft_free_line(char *line)
{
	free(line);
	line = NULL;
	return (line);
}

int		ft_press(int keycode, t_mega *mega)
{
	if (keycode == 13)
		mega->win.forward = 1;
	if (keycode == 0)
		mega->win.left = 1;
	if (keycode == 1)
		mega->win.backward = 1;
	if (keycode == 2)
		mega->win.right = 1;
	if (keycode == 123)
		mega->win.cam_left = 1;
	if (keycode == 124)
		mega->win.cam_right = 1;
	if (keycode == 53)
	{
		mlx_destroy_window(mega->win.mlx, mega->win.mlx_win);
		exit(0);
	}
	if (keycode == 17)
	{
		mlx_destroy_window(mega->win.mlx, mega->win.mlx_win);
		exit(0);
	}
	return (1);
}

int		ft_release(int keycode, t_mega *mega)
{
	if (keycode == 13)
		mega->win.forward = 0;
	if (keycode == 0)
		mega->win.left = 0;
	if (keycode == 1)
		mega->win.backward = 0;
	if (keycode == 2)
		mega->win.right = 0;
	if (keycode == 123)
		mega->win.cam_left = 0;
	if (keycode == 124)
		mega->win.cam_right = 0;
	return (0);
}
