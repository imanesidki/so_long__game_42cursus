/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:17:45 by isidki            #+#    #+#             */
/*   Updated: 2023/05/12 01:21:06 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft(void)
{
	system("leaks so_long");
}

int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		write(2, "failed to open the file", 23);
		exit (0);
	}
	return (fd);
}

int	ft_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_lines(data->lines);
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

void	parsing_map(char **lines, t_data *data)
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
			&& lines[i][j] != 'C' && lines[i][j] != '0')
				exit_error("invalid character in map");
		}
	}
	check_rectangular(lines, data);
	check_number_characters(lines, data);
	position_player(lines, data);
	j = valid_path(lines, data->x_player, data->y_player, data->nbr_collectb);
	if (j == 0)
		exit_error("invalid path in map");
}

void	ft_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_error("mlx_error");
	data->mlx_win = mlx_new_window(data->mlx_ptr,
			data->x * 50, data->y * 50, "Demon Slayer");
	ft_put_img(data);
	mlx_hook(data->mlx_win, 2, 0, &ft_check, data);
	mlx_hook(data->mlx_win, 17, 0, &ft_close, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	// atexit(ft);
	t_data	data;
	char	**lines;
	int		j;
	int		i;

	lines = NULL;
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
		ft_mlx(&data);
	}
	return (0);
}
