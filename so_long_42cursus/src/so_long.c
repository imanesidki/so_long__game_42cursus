/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:17:45 by isidki            #+#    #+#             */
/*   Updated: 2023/05/08 21:26:16 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft(void)
{
	system("leaks so_long");
}

char	**remplir_lines_parsing(char *file, int size)
{
	char	**lines;
	char	*line;
	int		fd;
	int		i;

	lines = (char **)malloc(sizeof(char *) * (size + 1));
	if (!lines)
		return (0);
	fd = ft_open(file);
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		lines[++i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	lines[++i] = NULL;
	return (lines);
}

char	**remplir_lines(char *file, int size)
{
	char	**lines;
	char	*line;
	int		fd;
	int		i;

	lines = (char **)malloc(sizeof(char *) * (size + 1));
	if (!lines)
		return (0);
	fd = ft_open(file);
	i = 0;
	line = get_next_line(fd);
	while (line &&  i < size)
	{
		if (i < size - 1)
		{
			lines[i] = ft_strdup_new(line);
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			lines[i] = ft_strdup(line);
			free(line);
		}
		i++;
	}
	lines[i] = NULL;
	return (lines);
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

void	free_lines(char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
		free(lines[i]);
	free(lines);
}

void	ft_xpm_image(t_data *data)
{
	printf("width , height :(%d), (%d)\n", data->img_width, data->img_height);
	data->img_c = mlx_xpm_file_to_image(data->mlx_ptr,
			"../xpm/deamon.xpm", &data->img_width, &data->img_height);
	if (!data->img_c)
		exit_error("error in openning collectible image");
	data->img_0 = mlx_xpm_file_to_image(data->mlx_ptr,
			"../xpm/white_img.xpm", &data->img_width, &data->img_height);
	if (!data->img_0)
		exit_error("error in openning road image");
	data->img_p = mlx_xpm_file_to_image(data->mlx_ptr,
			"../xpm/tanjirorun.xpm", &data->img_width, &data->img_height);
	if (!data->img_p)
		exit_error("error in openning player image");
	data->img_e = mlx_xpm_file_to_image(data->mlx_ptr,
			"../xpm/door.xpm", &data->img_width, &data->img_height);
	if (!data->img_e)
		exit_error("error in openning exit image");
	data->img_w = mlx_xpm_file_to_image(data->mlx_ptr,
			"../xpm/wall.xpm", &data->img_width, &data->img_height);
	if (!data->img_w)
		exit_error("error in openning wall image");
}

void	ft_image_to_win1(char **lines, t_data *data, int i, int j)
{
	if (lines[i][j] == 'P')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->img_p, data->x_player * 50, data->y_player * 50) < 0)
			exit_error("mlx_error");
	}
	else if (lines[i][j] == '1')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_w, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else if (lines[i][j] == '0')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_0, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else
		ft_image_to_win2(lines, data, i, j);
}

void	ft_image_to_win2(char **lines, t_data *data, int i, int j)
{
	if (lines[i][j] == 'E')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_e, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else if (lines[i][j] == 'C')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_c, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
}

void	ft_put_img(char **lines, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	ft_xpm_image(data);
	while (lines[i])
	{
		j = 0;
		while (j < data->x)
		{
			ft_image_to_win1(lines, data, i, j);
			j++;
		}
		i++;
	}
}

void	ft_mlx(char **lines, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_error("mlx_error");
	data->mlx_win = mlx_new_window(data->mlx_ptr,
			data->x * 50, data->y * 50, "so_long");
	ft_put_img(lines, data);
	//mlx_hook(data->mlx_win, 2, 0, ft_check, data);
	//mlx_hook(data->mlx_win, 17, 0, ft_close, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	// atexit(ft);
	t_data	data;
	char	**lines;
	int		j;

	lines = NULL;
	if (ac == 2)
	{
		check_file_name(av[1]);
		ft_initialize(&data);
		j = nbr_lines(av[1], &data);
		lines = remplir_lines_parsing(av[1], j);
		parsing_map(lines, &data);
		free_lines(lines);
		lines = remplir_lines(av[1], j);
		// int i = -1;
		// while (lines[++i])
		// {
		// 	printf("lines :(%p)\n", lines[i]);
		// }
		ft_mlx(lines, &data);
		free_lines(lines);
	}
	return (0);
}
