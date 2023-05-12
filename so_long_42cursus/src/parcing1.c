/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:31:15 by isidki            #+#    #+#             */
/*   Updated: 2023/05/12 01:14:26 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	check_file_name(char *v)
{
	int	i;

	i = ft_strlen(v);
	if (i <= 4)
		exit_error("file_name");
	if (!ft_strcmp(ft_strchr(v, '.'), ".ber"))
		return ;
	exit_error("unvalid file name");
}

void	check_rectangular(char **lines, t_data *data)
{
	int	i;
	int	len;

	i = data->y - 1;
	len = ft_strlen(lines[i]);
	data->x = len;
	while (i-- > 0)
	{
		len = ft_strlen(lines[i]);
		if (len != data->x)
			exit_error("map is not rectangular");
	}
}

void	check_number_characters(char **lines, t_data *data)
{
	int	i;
	int	j;
	int	nbr_p;
	int	nbr_e;
	int	nbr_c;

	i = data->y - 1;
	nbr_p = 0;
	nbr_e = 0;
	nbr_c = 0;
	while (--i > 0)
	{
		j = -1;
		while (lines[i][++j])
		{
			if (lines[i][j] == 'P')
				nbr_p++;
			if (lines[i][j] == 'E')
				nbr_e++;
			if (lines[i][j] == 'C')
				data->nbr_collectb = ++nbr_c;
		}
	}
	if (nbr_c == 0 || nbr_e > 1 || nbr_p > 1)
		exit_error("unacceptable number of characters");
}
