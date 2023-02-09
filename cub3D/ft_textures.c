/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_textures.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 18:29:06 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		ft_get_addr_textures(t_mega *mega)
{
	mega->tex[NO].addr =
		mlx_get_data_addr(mega->tex[NO].img, &mega->tex[NO].bits_per_pixel,
				&mega->tex[NO].line_length, &mega->tex[NO].endian);
	mega->tex[EA].addr =
		mlx_get_data_addr(mega->tex[EA].img, &mega->tex[EA].bits_per_pixel,
				&mega->tex[EA].line_length, &mega->tex[EA].endian);
	mega->tex[WE].addr =
		mlx_get_data_addr(mega->tex[WE].img, &mega->tex[WE].bits_per_pixel,
				&mega->tex[WE].line_length, &mega->tex[WE].endian);
	mega->tex[SO].addr =
		mlx_get_data_addr(mega->tex[SO].img, &mega->tex[SO].bits_per_pixel,
				&mega->tex[SO].line_length, &mega->tex[SO].endian);
	mega->tex[SP].addr =
		mlx_get_data_addr(mega->tex[SP].img, &mega->tex[SP].bits_per_pixel,
				&mega->tex[SP].line_length, &mega->tex[SP].endian);
}

void		ft_upload_textures(t_mega *mega)
{
	mega->tex[NO].img =
		mlx_png_file_to_image(mega->win.mlx, mega->tex[NO].texture,
				&mega->tex[NO].tex_width, &mega->tex[NO].tex_height);
	mega->tex[EA].img =
		mlx_png_file_to_image(mega->win.mlx, mega->tex[EA].texture,
			&mega->tex[EA].tex_width, &mega->tex[EA].tex_height);
	mega->tex[WE].img =
		mlx_png_file_to_image(mega->win.mlx, mega->tex[WE].texture,
				&mega->tex[WE].tex_width, &mega->tex[WE].tex_height);
	mega->tex[SO].img =
		mlx_png_file_to_image(mega->win.mlx, mega->tex[SO].texture,
			&mega->tex[SO].tex_width, &mega->tex[SO].tex_height);
	mega->tex[SP].img =
		mlx_png_file_to_image(mega->win.mlx, mega->tex[SP].texture,
				&mega->tex[SP].tex_width, &mega->tex[SP].tex_height);
	if (!mega->tex[NO].img || !mega->tex[EA].img ||
				!mega->tex[WE].img || !mega->tex[SO].img || !mega->tex[SP].img)
	{
		write(1, "Error\nInvalid png file\n", 24);
		exit(0);
	}
	ft_get_addr_textures(mega);
}

void		ft_draw_walls(t_mega *mega, int dir)
{
	if (mega->tex[dir].tex_width > mega->ray.x &&
					mega->tex[dir].tex_height > mega->win.screen_w - 1)
		mega->texpos.tex_y =
			((int)mega->texpos.texpos) & (mega->tex[dir].line_length - 1) * 4;
	else
		mega->texpos.tex_y =
					(int)mega->texpos.texpos & (mega->tex[dir].line_length - 1);
	mega->texpos.texpos += mega->texpos.step;
	mega->win.color =
					((int *)mega->tex[dir].addr)[(mega->tex[dir].line_length *
						mega->texpos.tex_y / 4) + mega->texpos.tex_x];
	if (mega->win.color < 0)
		mega->win.color = 0;
	if (mega->ray.side == 1)
		mega->win.color = (mega->win.color >> 1) & 8355711;
}

void		ft_textures(t_mega *mega, int dir)
{
	mega->texpos.texnum = mega->win.map[mega->ray.mapy][mega->ray.mapx] - 1;
	if (mega->ray.side == 0)
		mega->texpos.wallx =
				mega->ray.posy + mega->ray.perpwalldist * mega->ray.raydiry;
	else
		mega->texpos.wallx =
			mega->ray.posx + mega->ray.perpwalldist * mega->ray.raydirx;
	mega->texpos.wallx -= floor((mega->texpos.wallx));
	mega->texpos.tex_x =
		(int)(mega->texpos.wallx * (double)mega->tex[dir].tex_width);
	if (mega->ray.side == 0 && mega->ray.raydirx > 0)
		mega->texpos.tex_x =
			mega->tex[dir].tex_width - mega->texpos.tex_x - 1;
	if (mega->ray.side == 1 && mega->ray.raydiry < 0)
		mega->texpos.tex_x =
			mega->tex[dir].tex_width - mega->texpos.tex_x - 1;
	mega->texpos.step = 1.0 * mega->tex[dir].tex_height / mega->win.lineheight;
	mega->texpos.texpos =
		(mega->win.drawstart - mega->win.screen_h / 2 +
			mega->win.lineheight / 2) * mega->texpos.step;
}
