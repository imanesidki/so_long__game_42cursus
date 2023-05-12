/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:01:28 by isidki            #+#    #+#             */
/*   Updated: 2023/05/12 01:16:35 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putchar(char c)

{
	write (1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long int	i;

	i = nb;
	if (i < 0)
	{
		ft_putchar ('-');
		i *= -1;
	}
	if (i < 10)
	{
		ft_putchar (i + 48);
	}
	if (i >= 10)
	{
		ft_putnbr ((i / 10));
		ft_putnbr ((i % 10));
	}
}

int	exit_player(t_data *data)
{
	write(1, "Win !\n", 6);
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	free_lines(data->lines);
	exit (0);
}

void	exit_error(char *str)
{
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit (1);
}

void	free_lines(char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
		free(lines[i]);
	free(lines);
}
