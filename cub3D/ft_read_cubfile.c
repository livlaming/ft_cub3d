/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_read_cubfile.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/14 11:17:07 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		ft_find_colors_res(char *line, t_mega *mega, int i)
{
	if (line[i] == 'F' && mega->parser.floor == NULL)
		mega->parser.floor = ft_strdup(&line[i + 1]);
	else if (line[i] == 'F' && mega->parser.floor != NULL)
		ft_error_message(6);
	if (line[i] == 'C' && mega->parser.ceiling == NULL)
		mega->parser.ceiling = ft_strdup(&line[i + 1]);
	else if (line[i] == 'C' && mega->parser.ceiling != NULL)
		ft_error_message(7);
	if (line[i] == 'R' && mega->parser.res == NULL)
		mega->parser.res = ft_strdup(&line[i + 1]);
	else if (line[i] == 'R' && mega->parser.res != NULL)
		ft_error_message(8);
}

static void		ft_find_elements(char *line, t_mega *mega, int i)
{
	if (ft_strrchr("OEA", line[i + 1]) && line[i + 2] == ' ')
	{
		if (line[i] == 'N' && mega->tex[NO].texture == NULL)
			mega->tex[NO].texture = ft_strdup(&line[i + 2]);
		else if (line[i] == 'S' && mega->tex[SO].texture == NULL)
			mega->tex[SO].texture = ft_strdup(&line[i + 2]);
		else if (line[i] == 'E' && mega->tex[EA].texture == NULL)
			mega->tex[EA].texture = ft_strdup(&line[i + 2]);
		else if (line[i] == 'W' && mega->tex[WE].texture == NULL)
			mega->tex[WE].texture = ft_strdup(&line[i + 2]);
		else
			ft_error_message(4);
	}
	else if (line[i + 1] == ' ')
	{
		if (line[i] == 'S' && mega->tex[SP].texture == NULL)
			mega->tex[SP].texture = ft_strdup(&line[i + 1]);
		else if (line[i] == 'S' && mega->tex[SP].texture != NULL)
			ft_error_message(5);
		ft_find_colors_res(line, mega, i);
	}
	else
		ft_error_message(9);
}

static int		ft_save_elements(char *line, t_mega *mega, int i)
{
	if (line[i] == '\0' && mega->parser.map_nl_check > 0)
		mega->parser.newline++;
	if (line[i] != '\0')
	{
		if (ft_strrchr("RNSWEFC", line[i]))
			ft_find_elements(line, mega, i);
		else if (ft_strrchr("012NSWE ", line[i]) && mega->tex[NO].texture
			&& mega->tex[SO].texture && mega->tex[EA].texture &&
			mega->tex[WE].texture && mega->tex[SP].texture &&
			mega->parser.floor && mega->parser.ceiling && mega->parser.res)
		{
			mega->parser.map_nl_check++;
			if (ft_save_map(line, mega, 0, NULL) == -1)
			{
				line = ft_free_line(line);
				return (-1);
			}
		}
		else
			ft_error_message(9);
		return (0);
	}
	if (!line[i] && mega->parser.ycounter > 1)
		mega->parser.map_check++;
	return (0);
}

static int		ft_read_line(t_mega *mega, char *line, int gnl_return, int fd)
{
	int check;

	check = 0;
	while (gnl_return == 1)
	{
		gnl_return = get_next_line(fd, &line);
		if (check == 0)
		{
			check = ft_save_elements(line, mega, 0);
			if (check < 0)
				return (-1);
			if (gnl_return == 0)
				break ;
			line = ft_free_line(line);
		}
	}
	if (close(fd) == -1)
	{
		line = ft_free_line(line);
		return (ft_error_message(3));
	}
	line = ft_free_line(line);
	return (0);
}

int				ft_read_cubfile(t_mega *mega, char *line, int gnl_return)
{
	int error;
	int	fd;

	error = 0;
	fd = open(mega->parser.file, O_RDONLY);
	if (fd == -1)
		return (ft_error_message(2));
	if (read(fd, 0, 0) == -1)
		return (ft_error_message(16));
	error = ft_read_line(mega, line, gnl_return, fd);
	if (error != 0)
		return (error);
	line = ft_free_line(line);
	return (0);
}
