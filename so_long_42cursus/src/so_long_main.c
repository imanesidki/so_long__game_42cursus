/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:17:45 by isidki            #+#    #+#             */
/*   Updated: 2023/05/13 21:32:34 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
