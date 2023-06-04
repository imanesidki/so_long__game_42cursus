/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:40:13 by isidki            #+#    #+#             */
/*   Updated: 2023/06/04 14:19:02 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_check_bonus(int key, void *param)
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
	ft_put_img_bonus(data);
	return (0);
}

int	ft_frame(void *param)
{
	t_data		*data;
	static int	inc;

	data = (t_data *)param;
	if (inc < 400)
		inc++;
	else
	{
		inc = 0;
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		ft_put_img_bonus(data);
		if (data->moves > 0)
		{
			mlx_string_put(data->mlx_ptr, data->mlx_win, 0, 0, 0xffffff,
				ft_itoa(data->moves));
		}
	}
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
	mlx_hook(data->mlx_win, 2, 0, ft_check_bonus, data);
	mlx_hook(data->mlx_win, 17, 0, ft_close, data);
	mlx_loop_hook(data->mlx_ptr, ft_frame, data);
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
		parsing_map_bonus(lines, &data);
		free_lines(lines);
		ft_mlx_bonus(&data);
	}
	return (0);
}
