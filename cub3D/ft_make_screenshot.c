/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_make_screenshot.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/07 15:05:40 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_bit_converter(unsigned char *header, int value)
{
	int		and;
	int		shift;
	int		i;

	i = 0;
	shift = 0;
	and = 255;
	while (i < 4)
	{
		header[i] = (value & and) >> shift;
		shift += 8;
		and <<= 8;
		i++;
	}
}

void	ft_bmp_header(t_mega *mega, int fd)
{
	int				padding;
	unsigned char	header[54];

	ft_bzero(header, 54);
	padding = (4 - (3 * mega->win.screen_w) % 4) % 4;
	ft_bit_converter(header, 66);
	ft_bit_converter(header + 1, 77);
	ft_bit_converter(header + 2, (54 + mega->win.screen_h *
				(mega->win.screen_w + padding) * 3));
	ft_bit_converter(header + 10, 54);
	ft_bit_converter(header + 14, 40);
	ft_bit_converter(header + 18, mega->win.screen_w);
	ft_bit_converter(header + 22, mega->win.screen_h);
	ft_bit_converter(header + 26, 1);
	ft_bit_converter(header + 28, 24);
	write(fd, header, 54);
}

void	create_screenshot(t_mega *mega, int fd, unsigned int color, int ret)
{
	int				padding;
	int				x;
	int				y;

	y = mega->win.screen_h - 1;
	padding = (4 - (3 * mega->win.screen_h) % 4) % 4;
	while (y >= 0)
	{
		x = 0;
		while (x < mega->win.screen_w)
		{
			color = *(unsigned int*)(mega->win.addr +
					(y * mega->win.line_length + x *
					(mega->win.bits_per_pixel / 8)));
			ret = write(fd, &color, 3);
			if (ret == -1)
			{
				write(1, "Error\nNo memory for screenshot\n", 31);
				exit(-1);
			}
			x++;
		}
		write(fd, "\0\0\0", padding);
		y--;
	}
}

void	ft_make_screenshot(t_mega *mega)
{
	int		fd;

	fd = open("screenshot.bmp", O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		write(1, "Error\n open failed -> screenshot not possible\n", 46);
		exit(-1);
	}
	if (mega->win.screen_w > 16384)
		mega->win.screen_w = 16384;
	if (mega->win.screen_h > 16384)
		mega->win.screen_h = 16384;
	ft_bmp_header(mega, fd);
	create_screenshot(mega, fd, 0, 0);
	exit(-1);
}
