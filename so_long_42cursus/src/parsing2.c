/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:30:09 by isidki            #+#    #+#             */
/*   Updated: 2023/05/08 20:16:05 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strdup_new(char *source)
{
	char	*dst;
	int		i;
	int		j;

	i = ft_strlen(source);
	j = -1;
	dst = (char *) malloc(i + 2);
	if (!dst)
		return (NULL);
	while (++j < i)
		dst[j] = source[j];
	dst[i] = '\n';
	dst[i + 1] = '\0';
	return (dst);
}

int	nbr_lines(char *av, t_data *data)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = ft_open(av);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	data->y = i;
	return (i);
}

void	check_file_name(char *v)
{
	int	i;

	i = ft_strlen(v);
	if (i <= 4)
		exit_error("file_name");
	if (!ft_strcmp(ft_strchr(v, '.'), ".ber"))
		return ;
	exit_error("unvalid file name");
}

int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2,"Error\n", 6);
		write(2, "failed to open the file",23);
		exit (0);
	}
	return (fd);
}

void	check_rectangular(char **lines, t_data *data)
{
	int	i;
	int	len;

	i = data->y - 1;
	len = ft_strlen(lines[i]);
	data->x = len;
	while (i-- > 0)
	{
		len = ft_strlen(lines[i]);
		if (len != data->x)
			exit_error("map is not rectangular");
	}
}

void	check_number_characters(char **lines, t_data *data)
{
	int	i;
	int	j;
	int	nbr_p;
	int	nbr_e;
	int	nbr_c;

	i = data->y - 1;
	nbr_p = 0;
	nbr_e = 0;
	nbr_c = 0;
	while (--i > 0)
	{
		j = -1;
		while (lines[i][++j])
		{
			if (lines[i][j] == 'P')
				nbr_p++;
			if (lines[i][j] == 'E')
				nbr_e++;
			if (lines[i][j] == 'C')
				data->nbr_collectb = ++nbr_c;
		}
	}
	if (nbr_c == 0 || nbr_e > 1 || nbr_p > 1)
		exit_error("unacceptable number of characters");
}
