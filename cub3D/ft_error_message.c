/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error_message.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/07 16:42:44 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		ft_error_message_part_three(int message)
{
	if (message == 20)
		write(1, "Error\nmap is too large for this game\n", 37);
	if (message == 21)
		write(1, "Error\nImpossible to rescale resolution input\n", 45);
	exit(0);
}

static int		ft_error_message_part_two(int message)
{
	if (message == 10)
		write(1, "Error\nInvalid map --> Missing walls?\n", 37);
	if (message == 11)
		write(1, "Error\nmlx init failed\n", 22);
	if (message == 12)
		write(1, "Error\nmlx new window failed\n", 28);
	if (message == 13)
		write(1, "Error\nmlx new img failed\n", 25);
	if (message == 14)
		write(1, "Error\nInvalid map -> Newline in map\n", 37);
	if (message == 15)
		write(1, "Error\nInvalid map\n", 18);
	if (message == 16)
		write(1, "Error\nDon't fool me with your directory!\n", 41);
	if (message == 17)
		write(1, "Error\nMissing map\n", 18);
	if (message == 18)
		write(1, "Error\nno map.cub found\n", 23);
	if (message == 19)
		write(1, "Error\ntoo many arguments\n", 25);
	if (message > 19)
		ft_error_message_part_three(message);
	if (message == 14 || message == 15 || message == 18 || message == 19)
		return (-1);
	exit(0);
}

int				ft_error_message(int message)
{
	if (message == 0)
		write(1, "Error\nInvalid Resolution\n", 25);
	if (message == 1)
		write(1, "Error\nInvalid color input\n", 26);
	if (message == 2)
		write(1, "Error\nmap open failed\n", 22);
	if (message == 3)
		write(1, "Error\nmap close failed\n", 23);
	if (message == 4)
		write(1, "Error\nToo many textures imports\n", 32);
	if (message == 5)
		write(1, "Error\nToo many sprites imports\n", 31);
	if (message == 6)
		write(1, "Error\nToo many Floor imports\n", 29);
	if (message == 7)
		write(1, "Error\nToo many Ceiling imports\n", 32);
	if (message == 8)
		write(1, "Error\nToo many Resolution imports\n", 34);
	if (message == 9)
		write(1, "Error\nInvalid map import\n", 25);
	if (message > 9)
		ft_error_message_part_two(message);
	if (message == 2 || message == 3)
		return (1);
	exit(0);
}
