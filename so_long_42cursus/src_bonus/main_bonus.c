/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:40:13 by isidki            #+#    #+#             */
/*   Updated: 2023/05/31 05:49:35 by isidki           ###   ########.fr       */
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

void	ft_image_to_win_bonus(t_data *data,int i,int j)
{
	int	frame;

	frame = -1;
	if (data->lines[i][j] == 'F')
	{
		while (++frame < 23)
		{
			if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
					data->img_enemy_frames[frame], j * 50, i * 50) < 0)
				exit_error("mlx_error");
		}
	}
}

char	*ft_itoa(int value, char* str)
{
	if (value == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (value < 0)
	{
		*str++ = '-';
		value = -value;
	}
	if (value / 10 != 0)
		ft_itoa(value / 10, str);
	*str++ = value % 10 + '0';
	*str = '\0';
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

void	ft_xpm_enemy_frames(t_data *data)
{
	int		i;
	char	a[2];
	char	*filename;

	filename = "xpm/demon_frame_";
	i = -1;
	while (++i < 23)
	{
		ft_itoa(i, a);
		ft_strcat(filename, a);
		ft_strcat(filename, ".xpm");
		data->img_enemy_frames[i] = mlx_xpm_file_to_image(data->mlx_ptr,
				filename, &data->img_width, &data->img_height);
		if (!data->img_enemy_frames[i])
			exit_error("error in openning enemy frame image");
		filename[16] = '\0';
	}
}

int	ft_check_bonus(int key, void *param) //a modifier
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
	//write count moves in window
	ft_put_img_bonus(data);
	return (0);
}

int	ft_frame(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	ft_put_img_bonus(data);
	return (0);
}

void	ft_mlx_bonus(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_error("mlx_error");
	data->mlx_win = mlx_new_window(data->mlx_ptr,
			data->x * 50, data->y * 50, "Demon Slayer");
	ft_put_img_bonus(data);
	// mlx_loop_hook(data->mlx_win, &ft_frame, data);
	mlx_hook(data->mlx_win, 2, 0, &ft_check_bonus, data);
	mlx_hook(data->mlx_win, 17, 0, &ft_close, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	**lines;
	int		j;
	int		i;

	i = -1;
	if (ac == 2)
	{
		check_file_name(av[1]);
		ft_initialize(&data);
		j = nbr_lines(av[1], &data);
		data.lines = (char **) malloc((j + 1) * sizeof(char *));
		lines = remplir_lines_parsing(av[1], j);
		while (++i < j)
			data.lines[i] = ft_strdup(lines[i]);
		data.lines[i] = NULL;
		parsing_map(lines, &data);
		free_lines(lines);
		ft_mlx_bonus(&data);
	}
	return (0);
}
