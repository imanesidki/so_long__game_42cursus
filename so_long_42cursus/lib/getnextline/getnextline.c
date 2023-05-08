/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:59:32 by isidki            #+#    #+#             */
/*   Updated: 2023/05/08 01:08:24 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/so_long.h"

char	*ft_strdup(char *source)
{
	char	*dst;
	int		i;
	int		j;

	i = ft_strlen(source);
	j = -1;
	dst = (char *) malloc(i + 1);
	if (!dst)
		return (NULL);
	while (++j < i)
		dst[j] = source[j];
	dst[i] = '\0';
	return (dst);
}

char	*read_buff(int fd, char *hold)
{
	int		ret;
	char	*buffer;
	char	*str;

	ret = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(hold), NULL);
	buffer[0] = 0;
	while (ret != 0 && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (free(buffer), NULL);
		buffer[ret] = 0;
		str = ft_strjoin_strings(hold, buffer);
		free(hold);
		hold = str;
	}
	return (free(buffer), hold);
}

char	*update(char *hold)
{
	int		i;
	char	*str;

	i = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (hold[i] == '\n')
		i++;
	str = ft_substrs(hold, i, ft_strlen(hold + i));
	return (free(hold), str);
}

char	*mygetline(char *hold)
{
	int		i;
	char	*str;

	i = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	str = ft_substrs(hold, 0, i);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*hold;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	hold = read_buff(fd, hold);
	if (!hold)
		return (NULL);
	if (!*hold)
		return (free(hold), hold = NULL, NULL);
	return (line = mygetline(hold), hold = update(hold), line);
}
