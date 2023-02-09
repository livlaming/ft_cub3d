/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/14 10:02:11 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char		**ft_create_map(t_mega *mega, int y)
{
	char	**map;
	int		start;
	int		len;

	start = 0;
	len = 0;
	map = malloc(sizeof(char *) * (mega->parser.ycounter));
	if (!map)
		return (NULL);
	while (y < (int)mega->parser.ycounter)
	{
		if (mega->parser.saver[start + len] == '.')
		{
			map[y] =
				ft_calloc((size_t)mega->win.map_w + 1, (size_t)sizeof(char));
			map[y] = ft_memset(map[y], ' ', mega->win.map_w);
			map[y] = ft_memcpy(map[y], &mega->parser.saver[start], len);
			y++;
			start += len;
			start++;
			len = 0;
		}
		len++;
	}
	return (map);
}

char		**ft_reverse_map(t_mega *mega, int y, int x)
{
	char	**map;
	int		len;

	len = ft_strlen(mega->win.map[y]);
	map = malloc(sizeof(char *) * (mega->parser.ycounter));
	if (!map)
		return (NULL);
	while (y < (int)mega->parser.ycounter)
	{
		len = ft_strlen(mega->win.map[y]);
		map[y] = ft_calloc((size_t)len + 1, (size_t)sizeof(char));
		len--;
		while (mega->win.map[y][x] != '\0')
		{
			map[y][x] = mega->win.map[y][len];
			x++;
			len--;
		}
		free(mega->win.map[y]);
		y++;
		x = 0;
	}
	free(mega->win.map);
	return (map);
}

char		**ft_reverse_map_ff(t_mega *mega, int y, int x)
{
	char	**map_ff;
	int		len;

	len = ft_strlen(mega->win.map_ff[y]);
	map_ff = malloc(sizeof(char *) * (mega->parser.ycounter));
	if (!map_ff)
		return (NULL);
	while (y < (int)mega->parser.ycounter)
	{
		len = ft_strlen(mega->win.map_ff[y]);
		map_ff[y] = ft_calloc((size_t)len + 1, (size_t)sizeof(char));
		len--;
		while (mega->win.map_ff[y][x] != '\0')
		{
			map_ff[y][x] = mega->win.map_ff[y][len];
			x++;
			len--;
		}
		free(mega->win.map_ff[y]);
		y++;
		x = 0;
	}
	free(mega->win.map_ff);
	return (map_ff);
}
