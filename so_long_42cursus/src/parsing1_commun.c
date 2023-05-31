/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:31:15 by isidki            #+#    #+#             */
/*   Updated: 2023/05/13 20:55:20 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	parsing_map(char **lines, t_data *data)
{
	int	i;
	int	j;

	i = data->y - 1;
	check_wall(lines, data);
	while (--i > 0)
	{
		j = -1;
		while (lines[i][++j])
		{
			if (lines[i][j] != '1' && lines[i][j] != 'E' && lines[i][j] != 'P'
			&& lines[i][j] != 'C' && lines[i][j] != '0')
				exit_error("invalid character in map");
		}
	}
	check_rectangular(lines, data);
	check_number_characters(lines, data);
	position_player(lines, data);
	j = valid_path(lines, data->x_player, data->y_player, data->nbr_collectb);
	if (j == 0)
		exit_error("invalid path in map");
}

int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		write(2, "failed to open the file", 23);
		exit (0);
	}
	return (fd);
}

void	free_lines(char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
		free(lines[i]);
	free(lines);
}

void	exit_error(char *str)
{
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit (1);
}
