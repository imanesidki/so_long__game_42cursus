/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:58:38 by isidki            #+#    #+#             */
/*   Updated: 2023/05/13 21:34:23 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	if (key == 123 || key == A)
		ft_left(data);
	else if (key == 124 || key == D)
		ft_right(data);
	else if (key == 125 || key == S)
		ft_down(data);
	else if (key == 126 || key == W)
		ft_up(data);
	else if (key == 53)
		ft_close(param);
	ft_open_door(data);
	ft_put_img(data);
	write(1, "moves : ", 8);
	ft_putnbr(data->moves);
	write(1, "\n", 1);
	return (0);
}

int	ft_up(t_data *data)
{
	if (data->lines[data->y_player - 1][data->x_player] == '0')
	{
		data->lines[data->y_player - 1][data->x_player] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->y_player--;
		data->moves++;
	}
	else if (data->lines[data->y_player - 1][data->x_player] == 'C')
	{
		data->lines[data->y_player - 1][data->x_player] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->y_player--;
		data->nbr_collectb--;
		data->moves++;
	}
	else if (data->lines[data->y_player - 1][data->x_player] == 'D')
		exit_player(data);
	return (0);
}

int	ft_down(t_data *data)
{
	if (data->lines[data->y_player + 1][data->x_player] == '0')
	{
		data->lines[data->y_player + 1][data->x_player] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->y_player++;
		data->moves++;
	}
	else if (data->lines[data->y_player + 1][data->x_player] == 'C')
	{
		data->lines[data->y_player + 1][data->x_player] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->y_player++;
		data->nbr_collectb--;
		data->moves++;
	}
	else if (data->lines[data->y_player + 1][data->x_player] == 'D')
		exit_player(data);
	return (0);
}

int	ft_right(t_data *data)
{
	if (data->lines[data->y_player][data->x_player + 1] == '0')
	{
		data->lines[data->y_player][data->x_player + 1] = 'R';
		data->lines[data->y_player][data->x_player] = '0';
		data->x_player++;
		data->moves++;
	}
	else if (data->lines[data->y_player][data->x_player + 1] == 'C')
	{
		data->lines[data->y_player][data->x_player + 1] = 'R';
		data->lines[data->y_player][data->x_player] = '0';
		data->x_player++;
		data->nbr_collectb--;
		data->moves++;
	}
	else if (data->lines[data->y_player][data->x_player + 1] == 'D')
		exit_player(data);
	return (0);
}

int	ft_left(t_data *data)
{
	if (data->lines[data->y_player][data->x_player - 1] == '0')
	{
		data->lines[data->y_player][data->x_player - 1] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->x_player--;
		data->moves++;
	}
	else if (data->lines[data->y_player][data->x_player - 1] == 'C')
	{
		data->lines[data->y_player][data->x_player - 1] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->x_player--;
		data->nbr_collectb--;
		data->moves++;
	}
	else if (data->lines[data->y_player][data->x_player - 1] == 'D')
		exit_player(data);
	return (0);
}
