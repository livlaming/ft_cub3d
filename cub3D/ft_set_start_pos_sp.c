/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_set_start_pos_sp.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 17:18:25 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_ini_sprite(t_mega *mega)
{
	mega->sp.sprites->x = 0;
	mega->sp.sprites->y = 0;
	mega->sp.numb_sprites = 0;
	return (0);
}

int	ft_ini_sp(t_mega *mega)
{
	mega->sp.zbuffer = NULL;
	mega->sp.sprite_order = 0;
	mega->sp.sprite_dist = 0;
	mega->sp.spritex = 0.0;
	mega->sp.spritey = 0.0;
	mega->sp.sprites = ft_calloc(1, (size_t)sizeof(t_sprite));
	if (!mega->sp.sprites)
		return (-1);
	mega->sp.spritex = 0.0;
	mega->sp.spritey = 0.0;
	mega->sp.invdet = 0.0;
	mega->sp.transformx = 0.0;
	mega->sp.transformy = 0.0;
	mega->sp.spritescreenx = 0;
	mega->sp.sprite_height = 0;
	mega->sp.spritewidth = 0;
	mega->sp.drawstarty = 0;
	mega->sp.drawstartx = 0;
	mega->sp.drawendx = 0;
	mega->sp.drawendy = 0;
	mega->sp.stripe = 0;
	mega->sp.sp_tex_x = 0;
	mega->sp.sp_tex_y = 0;
	mega->sp.vmove_screen = 0;
	return (0);
}
