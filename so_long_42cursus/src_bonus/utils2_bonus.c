/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 05:53:35 by isidki            #+#    #+#             */
/*   Updated: 2023/06/04 15:31:08 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_put_img_bonus(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	ft_xpm_image(data);
	ft_xpm_enemy_frames(data);
	while (data->lines[i])
	{
		j = 0;
		while (j < data->x)
		{
			ft_image_to_win1(data, i, j);
			ft_image_to_win_bonus(data, i, j);
			j++;
		}
		i++;
	}
}

void	ft_image_to_win_bonus(t_data *data, int i, int j)
{
	if (data->lines[i][j] == 'F')
	{
		if (data->num_frame < 23)
			data->num_frame++;
		else
			data->num_frame = 0;
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_enemy_frames[data->num_frame],
				j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
}

void	ft_xpm_enemy_frames(t_data *data)
{
	int		i;
	char	*a;
	char	*filename1;
	char	*filename;

	i = -1;
	while (++i < 23)
	{
		a = ft_itoa(i);
		filename1 = ft_strjoin_strings("xpm/demon_frame_", a);
		filename = ft_strjoin_strings(filename1, ".xpm");
		data->img_enemy_frames[i] = mlx_xpm_file_to_image(data->mlx_ptr,
				filename, &data->img_width, &data->img_height);
		free (filename1);
		free (filename);
		free (a);
		if (!data->img_enemy_frames[i])
			exit_error("error in openning enemy frame image");
	}
}
