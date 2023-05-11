/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:31:15 by isidki            #+#    #+#             */
/*   Updated: 2023/05/11 02:25:05 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	position_player(char **lines, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (lines[i][j] == 'P')
			{
				data->x_player = j;
				data->y_player = i;
			}
		}
	}
}

void	exit_error(char *str)
{
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit (1);
}

int	valid_path(char **lines, int x, int y, int c)
{
	static int	ex;
	static int	ctble;

	if (lines[y][x] == 'E')
	{
		ex = 1;
		return (0);
	}
	if (lines[y][x] == 'C')
		ctble++;
	lines[y][x] = '1';
	if (lines[y - 1][x] != '1')
		valid_path(lines, x, y - 1, c);
	if (lines[y + 1][x] != '1')
		valid_path(lines, x, y + 1, c);
	if (lines[y][x - 1] != '1')
		valid_path(lines, x - 1, y, c);
	if (lines[y][x + 1] != '1')
		valid_path(lines, x + 1, y, c);
	if (ex && c == ctble)
		return (1);
	return (0);
}

void	ft_initialize(t_data *data)
{
	data->mlx_ptr = NULL;
	data->img_c = NULL;
	data->img_0 = NULL;
	data->img_w = NULL;
	data->img_e_c = NULL;
	data->img_e_o = NULL;
	data->img_p = NULL;
	data->img_height = 0;
	data->img_width = 0;
	data->x = 0;
	data->y = 0;
	data->nbr_collectb = 0;
	data->x_player = 0;
	data->y_player = 0;
	data->moves = 0;
	data->lines = NULL;
}

void	check_wall(char **lines, t_data *data)
{
	int	i;
	int	j;

	i = data->y - 1;
	j = -1;
	while (lines[i][++j])
	{
		if (lines[i][j] != '1')
			exit_error("map not surrounded by wall (bottom wall)");
	}
	while (i-- > 0)
	{
		j = ft_strlen(lines[i]) - 1;
		if (lines[i][0] != '1' || lines[i][j] != '1')
			exit_error("map not surrounded by wall");
	}
	j = ft_strlen(lines[0]);
	while (--j > 0)
	{
		if (lines[0][j] != '1')
			exit_error("map not surrounded by wall (top wall)");
	}
}
