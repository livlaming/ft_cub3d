/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 16:03:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		ft_draw_vert(t_mega *mega)
{
	int dir;
	int y;

	y = 0;
	dir = ft_calc_dir(mega);
	while (y < mega->win.screen_h)
	{
		if (y >= mega->win.drawend)
			ft_my_mlx_pixel_put(&mega->win,
				mega->ray.x, y, mega->parser.floor_col);
		else if (y >= mega->win.drawstart &&
				mega->win.drawstart < mega->win.drawend)
		{
			ft_textures(mega, dir);
			ft_draw_walls(mega, dir);
			ft_my_mlx_pixel_put(&mega->win,
				mega->ray.x, y, mega->win.color);
			mega->win.drawstart++;
		}
		else
			ft_my_mlx_pixel_put(&mega->win, mega->ray.x,
					y, mega->parser.ceiling_col);
		y++;
	}
}

void			ft_raycast(t_mega *mega)
{
	mega->ray.x = 0;
	while (mega->ray.x < mega->win.screen_w)
	{
		ft_calc_pos_dir(mega);
		ft_calc_step_side_d(mega);
		ft_dda(mega);
		ft_calculate_dist(mega);
		ft_draw_vert(mega);
		mega->sp.zbuffer[mega->ray.x] = mega->ray.perpwalldist;
		mega->ray.x++;
	}
	if (mega->sp.numb_sprites > 0)
		ft_create_sprites(mega);
}
