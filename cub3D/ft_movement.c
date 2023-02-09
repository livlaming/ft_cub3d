/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_movement.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 16:03:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		ft_mov_camera_right(t_mega *mega)
{
	mega->ray.olddirx = mega->ray.dirx;
	mega->ray.dirx = mega->ray.dirx * cos(-mega->win.rot_speed) -
						mega->ray.diry * sin(-mega->win.rot_speed);
	mega->ray.diry = mega->ray.olddirx * sin(-mega->win.rot_speed) +
						mega->ray.diry * cos(-mega->win.rot_speed);
	mega->ray.oldplanex = mega->ray.planex;
	mega->ray.planex = mega->ray.planex * cos(-mega->win.rot_speed) -
						mega->ray.planey * sin(-mega->win.rot_speed);
	mega->ray.planey = mega->ray.oldplanex * sin(-mega->win.rot_speed) +
						mega->ray.planey * cos(-mega->win.rot_speed);
}

static void		ft_move_camera(t_mega *mega)
{
	if (mega->win.cam_left == 1)
	{
		mega->ray.olddirx = mega->ray.dirx;
		mega->ray.dirx = mega->ray.dirx * cos(mega->win.rot_speed) -
						mega->ray.diry * sin(mega->win.rot_speed);
		mega->ray.diry = mega->ray.olddirx * sin(mega->win.rot_speed) +
							mega->ray.diry * cos(mega->win.rot_speed);
		mega->ray.oldplanex = mega->ray.planex;
		mega->ray.planex = mega->ray.planex * cos(mega->win.rot_speed) -
							mega->ray.planey * sin(mega->win.rot_speed);
		mega->ray.planey = mega->ray.oldplanex * sin(mega->win.rot_speed) +
							mega->ray.planey * cos(mega->win.rot_speed);
	}
	if (mega->win.cam_right == 1)
		ft_mov_camera_right(mega);
}

static void		ft_move_for_backward(t_mega *mega)
{
	if (mega->win.forward == 1)
	{
		if (mega->win.map[(int)mega->ray.posy][(int)(mega->ray.posx +
		mega->ray.dirx * mega->win.mov_speed)] == '0')
			mega->ray.posx += mega->ray.dirx * mega->win.mov_speed;
		if (mega->win.map[(int)(mega->ray.posy + mega->ray.diry *
		mega->win.mov_speed)][(int)(mega->ray.posx)] == '0')
			mega->ray.posy += mega->ray.diry * mega->win.mov_speed;
	}
	if (mega->win.backward == 1)
	{
		if (mega->win.map[(int)mega->ray.posy][(int)(mega->ray.posx -
		mega->ray.dirx * mega->win.mov_speed)] == '0')
			mega->ray.posx -= mega->ray.dirx * mega->win.mov_speed;
		if (mega->win.map[(int)(mega->ray.posy - mega->ray.diry *
		mega->win.mov_speed)][(int)(mega->ray.posx)] == '0')
			mega->ray.posy -= mega->ray.diry * mega->win.mov_speed;
	}
}

static void		ft_move_left_right(t_mega *mega)
{
	if (mega->win.right == 1)
	{
		if (mega->win.map[(int)mega->ray.posy][(int)(mega->ray.posx +
		mega->ray.diry * mega->win.mov_speed)] == '0')
			mega->ray.posx += mega->ray.diry * mega->win.mov_speed;
		if (mega->win.map[(int)(mega->ray.posy - mega->ray.dirx *
		mega->win.mov_speed)][(int)(mega->ray.posx)] == '0')
			mega->ray.posy -= mega->ray.dirx * mega->win.mov_speed;
	}
	if (mega->win.left == 1)
	{
		if (mega->win.map[(int)mega->ray.posy][(int)(mega->ray.posx -
		mega->ray.diry * mega->win.mov_speed)] == '0')
			mega->ray.posx -= mega->ray.diry * mega->win.mov_speed;
		if (mega->win.map[(int)(mega->ray.posy + mega->ray.dirx *
		mega->win.mov_speed)][(int)(mega->ray.posx)] == '0')
			mega->ray.posy += mega->ray.dirx * mega->win.mov_speed;
	}
}

int				ft_movement(t_mega *mega)
{
	ft_move_camera(mega);
	ft_move_for_backward(mega);
	ft_move_left_right(mega);
	ft_raycast(mega);
	mlx_put_image_to_window(mega->win.mlx,
		mega->win.mlx_win, mega->win.img, 0, 0);
	mlx_sync(3, mega->win.mlx_win);
	return (1);
}
