/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calc_dist_sprite.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 16:03:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_calc_dist_sprites(t_mega *mega, size_t sp)
{
	while (sp < mega->sp.numb_sprites)
	{
		mega->sp.sprite_order[sp] = sp;
		mega->sp.sprite_dist[sp] =
					(pow(mega->ray.posx - ((double)mega->sp.sprites[sp].x), 2) +
				pow(mega->ray.posy - ((double)mega->sp.sprites[sp].y), 2));
		sp++;
	}
}

void	ft_sort_sprites(t_mega *mega)
{
	double	order_temp;
	int		dist_temp;
	int		sp;

	order_temp = 0.0;
	dist_temp = 0;
	sp = 0;
	while ((unsigned long)sp < mega->sp.numb_sprites - 1)
	{
		if (mega->sp.sprite_dist[sp] < mega->sp.sprite_dist[sp + 1])
		{
			order_temp = mega->sp.sprite_order[sp];
			mega->sp.sprite_order[sp] = mega->sp.sprite_order[sp + 1];
			mega->sp.sprite_order[sp + 1] = order_temp;
			dist_temp = mega->sp.sprite_dist[sp];
			mega->sp.sprite_dist[sp] = mega->sp.sprite_dist[sp + 1];
			mega->sp.sprite_dist[sp + 1] = dist_temp;
			sp = -1;
		}
		sp++;
	}
}
