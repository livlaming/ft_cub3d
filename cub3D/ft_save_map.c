/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_save_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/14 11:16:11 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char		ft_set_dir(t_mega *mega, int x, char dir)
{
	if (dir == 'E')
	{
		mega->ray.planex = 0;
		mega->ray.planey = 0.66;
		mega->ray.dirx = -1;
		mega->ray.diry = 0;
	}
	if (dir == 'W')
	{
		mega->ray.planex = 0;
		mega->ray.planey = -0.66;
		mega->ray.dirx = 1;
		mega->ray.diry = 0;
	}
	if (dir == 'S')
	{
		mega->ray.planex = 0.66;
		mega->ray.planey = 0;
		mega->ray.dirx = 0;
		mega->ray.diry = 1;
	}
	mega->ray.x_temp = x;
	mega->ray.posy = mega->parser.ycounter + 0.5;
	mega->parser.dir_check++;
	return ('0');
}

static char		ft_set_positions(t_mega *mega, char *line, int x)
{
	int linelen;

	linelen = 0;
	if (line[x] == '2')
		mega->sp.numb_sprites++;
	if (ft_strrchr("NSWE", line[x]))
		line[x] = ft_set_dir(mega, x, line[x]);
	if (mega->parser.dir_check > 1)
	{
		mega->parser.dir_check = 0;
		write(1, "Error\nToo many Startpos\n", 24);
		exit(-1);
	}
	return (line[x]);
}

int				ft_save_map(char *line, t_mega *mega, int x, char *temp)
{
	if (mega->parser.newline > 0)
		ft_error_message(14);
	while (line[x] != '\0')
	{
		if (mega->parser.map_check > 0)
			return (ft_error_message(14));
		if (ft_strrchr("012NWSE ", line[x]) != NULL
									&& mega->parser.dir_check != 2)
			line[x] = ft_set_positions(mega, line, x);
		else
			return (ft_error_message(15));
		x++;
	}
	temp = ft_strjoin(mega->parser.saver, line);
	free(mega->parser.saver);
	mega->parser.saver = ft_strjoin(temp, ".");
	free(temp);
	temp = NULL;
	mega->parser.ycounter++;
	if (x > (int)mega->win.map_w)
		mega->win.map_w = (double)x;
	return (0);
}
