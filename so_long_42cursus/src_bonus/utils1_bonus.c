/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 05:46:38 by isidki            #+#    #+#             */
/*   Updated: 2023/06/01 05:52:51 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	count_digit(int n)
{
	int	nbr;

	nbr = 0;
	if (n < 0)
		nbr++;
	while (n)
	{
		nbr++;
		n /= 10;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = n;
	i = count_digit(n);
	if (n == 0)
		return (ft_strdup("0"));
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
		nb *= -1;
	str[i] = '\0';
	while (--i >= 0)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_strcat(char *dest, char *src)
{
	int	len_dest;
	int	i;

	i = 0;
	len_dest = ft_strlen (dest);
	while (src[i] != '\0')
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (dest);
}

int	valid_path_bonus(char **lines, int x, int y, int c)
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
	if (lines[y - 1][x] != '1' && lines[y - 1][x] != 'F')
		valid_path_bonus(lines, x, y - 1, c);
	if (lines[y + 1][x] != '1' && lines[y + 1][x] != 'F')
		valid_path_bonus(lines, x, y + 1, c);
	if (lines[y][x - 1] != '1' && lines[y][x - 1] != 'F')
		valid_path_bonus(lines, x - 1, y, c);
	if (lines[y][x + 1] != '1' && lines[y][x + 1] != 'F')
		valid_path_bonus(lines, x + 1, y, c);
	if (ex && c == ctble)
		return (1);
	return (0);
}

void	parsing_map_bonus(char **lines, t_data *data)
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
			&& lines[i][j] != 'C' && lines[i][j] != '0' && lines[i][j] != 'F')
				exit_error("invalid character in map");
		}
	}
	check_rectangular(lines, data);
	check_number_characters(lines, data);
	position_player(lines, data);
	j = valid_path_bonus(lines, data->x_player, data->y_player,
			data->nbr_collectb);
	if (j == 0)
		exit_error("invalid path in map");
}
