/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_set_start_pos.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/14 11:10:58 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_ini_win(t_mega *mega)
{
	mega->win.mlx = 0;
	mega->win.mlx_win = 0;
	mega->win.bits_per_pixel = 0;
	mega->win.endian = 0;
	mega->win.line_length = 0;
	mega->win.addr = 0;
	mega->win.lineheight = 0;
	mega->win.drawstart = 0;
	mega->win.drawend = 0;
	mega->win.color = 0x0000FF00;
	mega->win.mov_speed = 0.07;
	mega->win.rot_speed = 0.07;
	mega->win.map = NULL;
	mega->win.forward = 0;
	mega->win.backward = 0;
	mega->win.left = 0;
	mega->win.right = 0;
	mega->win.destroy = 0;
	mega->win.map_ff = NULL;
	mega->win.screen_w = 0;
	mega->win.screen_h = 0;
	mega->win.map_w = 0;
	return (0);
}

int	ft_ini_ray(t_mega *mega)
{
	mega->ray.posx = 0;
	mega->ray.posy = 0;
	mega->ray.dirx = 0;
	mega->ray.diry = -1;
	mega->ray.planex = -0.66;
	mega->ray.planey = 0;
	mega->ray.time = 0;
	mega->ray.old_time = 0;
	mega->ray.x = 0;
	mega->ray.camerax = 0;
	mega->ray.raydirx = 0;
	mega->ray.raydiry = 0;
	mega->ray.mapx = 0;
	mega->ray.mapy = 0;
	mega->ray.sidedistx = 0;
	mega->ray.sidedisty = 0;
	mega->ray.perpwalldist = 0;
	mega->ray.stepx = 0;
	mega->ray.stepy = 0;
	mega->ray.hit = 0;
	mega->ray.side = 0;
	mega->ray.oldplanex = 0;
	mega->ray.olddirx = 0;
	mega->ray.x_temp = 0;
	return (0);
}

int	ft_ini_textures(t_tex *tex, int i)
{
	tex[i].img = NULL;
	tex[i].addr = NULL;
	tex[i].endian = 0;
	tex[i].bits_per_pixel = 0;
	tex[i].line_length = 0;
	tex[i].tex_width = 0;
	tex[i].tex_height = 0;
	tex[i].texture = NULL;
	return (0);
}

int	ft_ini_parser(t_mega *mega)
{
	mega->parser.map_nl_check = 0;
	mega->parser.file = NULL;
	mega->parser.start_dir = 0;
	mega->parser.res = NULL;
	mega->parser.floor = NULL;
	mega->parser.ceiling = NULL;
	mega->parser.screenshot = 0;
	mega->parser.rgb_check = 0;
	mega->parser.saver = ft_strdup("");
	if (!mega->parser.saver)
		return (-1);
	mega->parser.ycounter = 0;
	mega->parser.map_check = 0;
	mega->parser.dir_check = 0;
	mega->parser.floor_col = 0;
	mega->parser.ceiling_col = 0;
	mega->parser.newline = 0;
	return (0);
}

int	ft_ini_all_textures(t_mega *mega)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (ft_ini_textures(mega->tex, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
