/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/07 17:01:18 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		ft_check_arg(int argc, char **argv, t_mega *mega)
{
	argv++;
	if (argc == 1)
		ft_error_message(18);
	if (argc < 4)
	{
		mega->parser.file = ft_strdup(*argv);
		if (ft_strncmp(*argv + (ft_strlen(*argv) - 4), ".cub", 4))
			ft_error_message(18);
		if (argc == 3)
		{
			argv++;
			if (!ft_strncmp(*argv, "--save", 7))
				mega->parser.screenshot = 1;
		}
	}
	if (argc > 3 || (mega->parser.screenshot == 0 && argc == 3))
		ft_error_message(19);
	return (0);
}

static void		ft_make_space_sp(t_mega *mega)
{
	mega->sp.zbuffer = ft_calloc(mega->win.screen_w, sizeof(double));
	mega->sp.sprite_order = ft_calloc(mega->sp.numb_sprites, sizeof(int));
	mega->sp.sprite_dist = ft_calloc(mega->sp.numb_sprites, sizeof(double));
}

static void		ft_set_startposx(t_mega *mega)
{
	mega->win.map_w--;
	mega->win.map_w -= mega->ray.x_temp;
	mega->ray.posx = mega->win.map_w + 0.5;
}

static int		ft_map(t_mega *mega)
{
	if (mega->parser.saver[0] == '\0' || !mega->parser.saver)
		ft_error_message(17);
	mega->win.map = ft_create_map(mega, 0);
	mega->win.map_ff = ft_create_map(mega, 0);
	if (mega->win.map == NULL || mega->win.map_ff == NULL)
		return (-1);
	mega->win.map = ft_reverse_map(mega, 0, 0);
	mega->win.map_ff = ft_reverse_map_ff(mega, 0, 0);
	if (mega->win.map == NULL || mega->win.map_ff == NULL)
		return (-1);
	return (0);
}

int				main(int argc, char **argv)
{
	t_mega	*mega;

	mega = (t_mega *)malloc(sizeof(t_mega));
	if (!mega)
		return (-1);
	if ((ft_ini_win(mega) == -1) || (ft_ini_ray(mega) == -1) ||
			(ft_ini_all_textures(mega) == -1) || (ft_ini_parser(mega) == -1) ||
				(ft_ini_sp(mega) == -1) || (ft_ini_sprite(mega) == -1))
		return (-1);
	if (ft_check_arg(argc, argv, mega) != 0)
		return (-1);
	if (ft_read_cubfile(mega, NULL, 1) != 0)
		return (-1);
	if (ft_map(mega) == -1)
		return (-1);
	ft_set_startposx(mega);
	if (ft_check_data(mega) == -1)
		return (-1);
	ft_make_space_sp(mega);
	ft_cub(mega);
	return (0);
}
