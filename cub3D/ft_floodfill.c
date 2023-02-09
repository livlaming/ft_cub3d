/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_floodfill.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/07 15:46:15 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		flood_fill_conditions(int x, int y, char fill, t_mega *mega)
{
	if (!mega->win.map_ff[y][x] || y < 0 || x < 0 ||
			mega->win.map_ff[y][x] == ' ')
		return (-1);
	if (mega->win.map_ff[y][x] != '1' &&
			(x == 0 || y == 0 || y == (int)mega->parser.ycounter - 1))
		return (-1);
	if (mega->win.map_ff[y][x] == '1' || mega->win.map_ff[y][x] == fill)
		return (0);
	if (x - 1 < 0 || y - 1 < 0)
		return (-1);
	if (x >= (int)ft_strlen(mega->win.map_ff[y - 1]) ||
			x >= (int)ft_strlen(mega->win.map_ff[y + 1]))
		return (-1);
	return (2);
}

int		flood_fill(int x, int y, char fill, t_mega *mega)
{
	int check;

	check = flood_fill_conditions(x, y, fill, mega);
	if (check != 2)
		return (check);
	mega->win.map_ff[y][x] = fill;
	if (flood_fill(x + 1, y, fill, mega) == -1)
		return (-1);
	if (flood_fill(x - 1, y, fill, mega) == -1)
		return (-1);
	if (flood_fill(x, y + 1, fill, mega) == -1)
		return (-1);
	if (flood_fill(x, y - 1, fill, mega) == -1)
		return (-1);
	if (flood_fill(x + 1, y + 1, fill, mega) == -1)
		return (-1);
	if (flood_fill(x - 1, y + 1, fill, mega) == -1)
		return (-1);
	if (flood_fill(x - 1, y - 1, fill, mega) == -1)
		return (-1);
	if (flood_fill(x + 1, y - 1, fill, mega) == -1)
		return (-1);
	return (0);
}
