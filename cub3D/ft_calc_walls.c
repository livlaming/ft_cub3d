/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calc_walls.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 16:03:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		ft_calc_pos_dir(t_mega *mega)
{
	mega->ray.camerax = 2 * mega->ray.x / (double)mega->win.screen_w - 1;
	mega->ray.raydirx = mega->ray.dirx + mega->ray.planex * mega->ray.camerax;
	mega->ray.raydiry = mega->ray.diry + mega->ray.planey * mega->ray.camerax;
	mega->ray.mapx = (int)mega->ray.posx;
	mega->ray.mapy = (int)mega->ray.posy;
	mega->ray.deltadistx = fabs(1 / mega->ray.raydirx);
	mega->ray.deltadisty = fabs(1 / mega->ray.raydiry);
	mega->ray.hit = 0;
}

void		ft_calc_step_side_d(t_mega *mega)
{
	if (mega->ray.raydirx < 0)
	{
		mega->ray.stepx = -1;
		mega->ray.sidedistx =
			(mega->ray.posx - mega->ray.mapx) * mega->ray.deltadistx;
	}
	else
	{
		mega->ray.stepx = 1;
		mega->ray.sidedistx =
			(mega->ray.mapx + 1.0 - mega->ray.posx) * mega->ray.deltadistx;
	}
	if (mega->ray.raydiry < 0)
	{
		mega->ray.stepy = -1;
		mega->ray.sidedisty =
			(mega->ray.posy - mega->ray.mapy) * mega->ray.deltadisty;
	}
	else
	{
		mega->ray.stepy = 1;
		mega->ray.sidedisty =
			(mega->ray.mapy + 1.0 - mega->ray.posy) * mega->ray.deltadisty;
	}
}

void		ft_dda(t_mega *mega)
{
	while (mega->ray.hit == 0)
	{
		if (mega->ray.sidedistx < mega->ray.sidedisty)
		{
			mega->ray.sidedistx += mega->ray.deltadistx;
			mega->ray.mapx += mega->ray.stepx;
			mega->ray.side = 0;
		}
		else
		{
			mega->ray.sidedisty += mega->ray.deltadisty;
			mega->ray.mapy += mega->ray.stepy;
			mega->ray.side = 1;
		}
		if (mega->win.map[mega->ray.mapy][mega->ray.mapx] == '1')
			mega->ray.hit = 1;
	}
}

int			ft_calc_dir(t_mega *mega)
{
	int dir;

	dir = 0;
	if (mega->ray.side == 1)
	{
		if (mega->ray.raydiry > 0)
			dir = SO;
		else
			dir = NO;
	}
	if (mega->ray.side == 0)
	{
		if (mega->ray.raydirx < 0)
			dir = EA;
		else
			dir = WE;
	}
	return (dir);
}

void		ft_calculate_dist(t_mega *mega)
{
	if (mega->ray.side == 0)
		mega->ray.perpwalldist = (mega->ray.mapx -
			mega->ray.posx + (1 - mega->ray.stepx) / 2) / mega->ray.raydirx;
	else
		mega->ray.perpwalldist = (mega->ray.mapy -
			mega->ray.posy + (1 - mega->ray.stepy) / 2) / mega->ray.raydiry;
	mega->win.lineheight = (int)(mega->win.screen_h / mega->ray.perpwalldist);
	mega->win.drawstart = mega->win.screen_h / 2 - mega->win.lineheight / 2;
	if (mega->win.drawstart < 0)
		mega->win.drawstart = 0;
	mega->win.drawend = mega->win.lineheight / 2 + mega->win.screen_h / 2;
	if (mega->win.drawend >= mega->win.screen_h)
		mega->win.drawend = mega->win.screen_h;
}
