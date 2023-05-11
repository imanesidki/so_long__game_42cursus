/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:17:45 by isidki            #+#    #+#             */
/*   Updated: 2023/05/11 02:56:40 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft(void)
{
	system("leaks so_long");
}

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
	data->img_c = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/demon.xpm", &data->img_width, &data->img_height);
	if (!data->img_c)
		exit_error("error in openning collectible image");
	data->img_0 = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/white_img.xpm", &data->img_width, &data->img_height);
	if (!data->img_0)
		exit_error("error in openning road image");
	data->img_p = mlx_xpm_file_to_image(data->mlx_ptr,
			"xpm/tanjirorun.xpm", &data->img_width, &data->img_height);
	if (!data->img_p)
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
			data->img_p, data->x_player * 50, data->y_player * 50) < 0)
			exit_error("mlx_error");
	}
	else if (data->lines[i][j] == '1')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_w, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
	else if (data->lines[i][j] == '0')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_0, j * 50, i * 50) < 0)
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
	else if (data->lines[i][j] == 'C')
	{
		if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_c, j * 50, i * 50) < 0)
			exit_error("mlx_error");
	}
}

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

int	ft_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_lines(data->lines);
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

int	exit_player(t_data *data)
{
	write(1, "Win !\n", 6);
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	free_lines(data->lines);
	exit (0);
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

int	ft_right(t_data *data)
{
	if (data->lines[data->y_player][data->x_player + 1] == '0')
	{
		data->lines[data->y_player][data->x_player + 1] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->x_player++;
		data->moves++;
	}
	else if (data->lines[data->y_player][data->x_player + 1] == 'C')
	{
		data->lines[data->y_player][data->x_player + 1] = 'P';
		data->lines[data->y_player][data->x_player] = '0';
		data->x_player++;
		data->nbr_collectb--;
		data->moves++;
	}
	else if (data->lines[data->y_player][data->x_player + 1] == 'D')
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

int	ft_open_door(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	if (!data->nbr_collectb)
	{
		while(data->lines[++i])
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
	ft_open_door(data);
	ft_put_img(data);
	write(1, "moves : ", 8);
	ft_putnbr(data->moves);
	write(1, "\n", 1);
	return (0);
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
