/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 15:52:14 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				ft_cub(t_mega *mega)
{
	mega->win.mlx = mlx_init();
	if (!mega->win.mlx)
		ft_error_message(11);
	mega->win.mlx_win = mlx_new_window(mega->win.mlx,
		mega->win.screen_w, mega->win.screen_h, "cub3D");
	if (!mega->win.mlx_win)
		ft_error_message(12);
	mega->win.img = mlx_new_image(mega->win.mlx,
		mega->win.screen_w, mega->win.screen_h);
	if (!mega->win.mlx)
		ft_error_message(13);
	mega->win.addr = mlx_get_data_addr(mega->win.img,
		&mega->win.bits_per_pixel, &mega->win.line_length, &mega->win.endian);
	ft_upload_textures(mega);
	ft_raycast(mega);
	if (mega->parser.screenshot == 1)
		ft_make_screenshot(mega);
	mlx_put_image_to_window(mega->win.mlx,
		mega->win.mlx_win, mega->win.img, 0, 0);
	mlx_hook(mega->win.mlx_win, 2, 1L << 0, ft_press, mega);
	mlx_hook(mega->win.mlx_win, 3, 1L << 0, ft_release, mega);
	mlx_hook(mega->win.mlx_win, 17, 1L << 17, ft_close_window, mega);
	mlx_loop_hook(mega->win.mlx, ft_movement, mega);
	mlx_loop(mega->win.mlx);
	return (0);
}
