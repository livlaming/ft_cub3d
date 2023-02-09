/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_rgb.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 19:22:51 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		ft_get_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static int		ft_scan_dig(t_mega *mega, char *color, int start)
{
	while (ft_isdigit(color[start]) == 1)
		start++;
	while (color[start] == ',' || color[start] == ' ')
	{
		if (color[start] == ',')
			mega->parser.rgb_check++;
		start++;
	}
	return (start);
}

int				ft_check_rgb(t_mega *mega, char *color, int r, int g)
{
	int start;
	int	b;

	b = -1;
	start = 0;
	while (color[start] == ' ')
		start++;
	r = ft_atoi(&color[start]);
	start = ft_scan_dig(mega, color, start);
	g = ft_atoi(&color[start]);
	start = ft_scan_dig(mega, color, start);
	b = ft_atoi(&color[start]);
	while (ft_isdigit(color[start]) == 1)
		start++;
	while (color[start] != '\0')
	{
		if (color[start] != ' ')
			ft_error_message(1);
		start++;
	}
	if (r > 255 || g > 255 || b > 255 || r < 0 ||
				g < 0 || b < 0 || mega->parser.rgb_check != 2)
		ft_error_message(1);
	mega->parser.rgb_check = 0;
	return (ft_get_hex(r, g, b));
}
