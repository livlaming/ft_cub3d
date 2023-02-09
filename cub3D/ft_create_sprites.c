/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_sprites.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 16:03:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		ft_spritex_spritey(t_mega *mega, int sp)
{
	mega->sp.spritex =
		mega->sp.sprites[mega->sp.sprite_order[sp]].x - mega->ray.posx;
	mega->sp.spritey =
		mega->sp.sprites[mega->sp.sprite_order[sp]].y - mega->ray.posy;
	mega->sp.invdet = 1.0 /
		(mega->ray.planex * mega->ray.diry - mega->ray.dirx * mega->ray.planey);
	mega->sp.transformx = mega->sp.invdet *
		(mega->ray.diry * mega->sp.spritex - mega->ray.dirx * mega->sp.spritey);
	mega->sp.transformy = mega->sp.invdet * (-mega->ray.planey *
					mega->sp.spritex + mega->ray.planex * mega->sp.spritey);
	mega->sp.spritescreenx = (int)((mega->win.screen_w / 2) *
							(1 + mega->sp.transformx / mega->sp.transformy));
}

static void		ft_translate_sprite(t_mega *mega)
{
	mega->sp.vmove_screen = (int)(VMOVE / mega->sp.transformy);
	mega->sp.sprite_height = abs((int)(mega->win.screen_h /
		(mega->sp.transformy))) / VDIV;
	mega->sp.drawstarty = -mega->sp.sprite_height /
		2 + mega->win.screen_h / 2 + mega->sp.vmove_screen;
	if (mega->sp.drawstarty < 0)
		mega->sp.drawstarty = 0;
	mega->sp.drawendy = (mega->sp.sprite_height /
		2 + mega->win.screen_h / 2 + mega->sp.vmove_screen);
	if (mega->sp.drawendy >= mega->win.screen_h)
		mega->sp.drawendy = mega->win.screen_h - 1;
	mega->sp.spritewidth =
		abs((int)(mega->win.screen_h / (mega->sp.transformy))) / UDIV;
	mega->sp.drawstartx =
		(int)(-mega->sp.spritewidth / 2 + mega->sp.spritescreenx);
	if (mega->sp.drawstartx < 0)
		mega->sp.drawstartx = 0;
	mega->sp.drawendx = mega->sp.spritewidth / 2 + mega->sp.spritescreenx;
	if (mega->sp.drawendx >= mega->win.screen_w)
		mega->sp.drawendx = mega->win.screen_w - 1;
}

static void		ft_draw_line_sp(t_mega *mega, int color, int x, int d)
{
	int y;

	y = mega->sp.drawstarty;
	while (y < mega->sp.drawendy)
	{
		d = (y - mega->sp.vmove_screen) * 256 - mega->win.screen_h *
					128 + mega->sp.sprite_height * 128;
		mega->sp.sp_tex_y = ((d * mega->tex[SP].tex_height) /
								mega->sp.sprite_height) / 256;
		if (mega->sp.sp_tex_x >= 0 && mega->sp.sp_tex_y >= 0 &&
					mega->sp.sp_tex_x < mega->tex[SP].tex_width)
		{
			color = *(unsigned int*)(mega->tex[SP].addr +
					(mega->sp.sp_tex_y * mega->tex[SP].line_length +
						mega->sp.sp_tex_x * (mega->tex[SP].bits_per_pixel /
							8)));
		}
		if (color < 0)
			color = 0;
		if (color > 0)
			ft_my_mlx_pixel_put(&mega->win, x, y, color);
		y++;
	}
}

static void		ft_draw_sprites(t_mega *mega, int d, int color)
{
	int x;

	x = mega->sp.drawstartx;
	while (x < mega->sp.drawendx)
	{
		mega->sp.sp_tex_x = (int)(256 *
			(x - (-mega->sp.spritewidth / 2 + mega->sp.spritescreenx)) *
					mega->tex[SP].tex_width / mega->sp.spritewidth / 256);
		if (mega->sp.transformy > 0 && x > 0 && x < mega->win.screen_w &&
					mega->sp.transformy < mega->sp.zbuffer[x])
		{
			ft_draw_line_sp(mega, color, x, d);
		}
		x++;
	}
}

void			ft_create_sprites(t_mega *mega)
{
	int	sp;

	sp = 0;
	ft_calc_dist_sprites(mega, 0);
	ft_sort_sprites(mega);
	while ((double)sp < mega->sp.numb_sprites)
	{
		ft_spritex_spritey(mega, sp);
		ft_translate_sprite(mega);
		ft_draw_sprites(mega, 0, 0);
		sp++;
	}
	mega->sp.vmove_screen = 0;
	free(mega->sp.zbuffer);
	mega->sp.zbuffer = ft_calloc(mega->win.screen_w, sizeof(double));
}
