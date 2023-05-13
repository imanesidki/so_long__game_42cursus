/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:40:13 by isidki            #+#    #+#             */
/*   Updated: 2023/05/12 22:05:37 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	char	**lines;
	int		j;
	int		i;

	// lines = NULL;
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
		// ft_mlx_bonus(&data);
	}
	return (0);
}
