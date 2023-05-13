/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:51:50 by isidki            #+#    #+#             */
/*   Updated: 2023/05/12 20:11:03 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_img(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	ft_xpm_image(data);
	while (data->lines[i])
	{
		j = 0;
		while (j < data->x)
		{
			ft_image_to_win1(data, i, j);
			j++;
		}
		i++;
	}
}

void	ft_xpm_image(t_data *data)
{
	data->img_c = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/sword.xpm", &data->img_width, &data->img_height);
	if (!data->img_c)
		exit_error("error in openning collectible image");
	data->img_0 = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/white_img.xpm", &data->img_width, &data->img_height);
	if (!data->img_0)
		exit_error("error in openning road image");
	data->img_p_l = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/tanjiro_left0.xpm", &data->img_width, &data->img_height);
	if (!data->img_p_l)
		exit_error("error in openning player image");
	data->img_p_r = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/tanjiro_right0.xpm", &data->img_width, &data->img_height);
	if (!data->img_p_r)
		exit_error("error in openning player image");
	ft_xpm_image2(data);
}

void	ft_xpm_image2(t_data *data)
{
	data->img_e_c = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/door_closed.xpm", &data->img_width, &data->img_height);
	if (!data->img_e_c)
		exit_error("error in openning exit image");
	data->img_e_o = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/door_opened.xpm", &data->img_width, &data->img_height);
	if (!data->img_e_o)
		exit_error("error in openning exit image");
	data->img_w = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/wall.xpm", &data->img_width, &data->img_height);
	if (!data->img_w)
		exit_error("error in openning wall image");
}

void	ft_image_to_win1(t_data *data, int i, int j)
{
	if (data->lines[i][j] == 'P')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_p_l, data->x_player * 50, data->y_player * 50) < 0)
			exit_error("mlx_error");
	}
	else if (data->lines[i][j] == 'R')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_p_r, data->x_player * 50, data->y_player * 50) < 0)
			exit_error("mlx_error");
	}
	else if (data->lines[i][j] == '1')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_w, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else
		ft_image_to_win2(data, i, j);
}

void	ft_image_to_win2(t_data *data, int i, int j)
{
	if (data->lines[i][j] == 'E')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_e_c, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else if (data->lines[i][j] == 'D')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_e_o, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else if (data->lines[i][j] == '0')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_0, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else if (data->lines[i][j] == 'C')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_c, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
}
