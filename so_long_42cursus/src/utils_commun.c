/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:01:28 by isidki            #+#    #+#             */
/*   Updated: 2023/06/01 05:18:24 by isidki           ###   ########.fr       */
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

int	ft_open_door(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	if (!data->nbr_collectb)
	{
		while (data->lines[++i])
		{
			j = -1;
			while (data->lines[i][++j])
			{
				if (data->lines[i][j] == 'E')
					data->lines[i][j] = 'D';
			}
		}
	}
	return (0);
}

int	ft_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_lines(data->lines);
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}
