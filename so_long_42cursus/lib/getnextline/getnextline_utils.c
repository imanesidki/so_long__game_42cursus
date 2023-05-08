/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:00:06 by isidki            #+#    #+#             */
/*   Updated: 2023/05/05 16:19:32 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/so_long.h"

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strchr(char *string, int c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	str = string;
	len = ft_strlen(string);
	while (i < len || c == '\0')
	{
		if (*(str + i) == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_strings(char *s1, char *s2)
{
	char	*str;
	char	*dup;
	int		i;
	int		j;

	if (!s1)
		dup = ft_strdup("");
	else
		dup = ft_strdup(s1);
	str = (char *)malloc(ft_strlen(s2) + ft_strlen(dup) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (dup[++i])
		str[i] = dup[i];
	while (s2[++j])
		str[i + j] = s2[j];
	return (str[i + j] = 0, free(dup), str);
}

char	*ft_substrs(char *s, unsigned int start, int len)
{
	char			*sub;
	int				i;
	unsigned int	srclen;

	if (!s)
		return (NULL);
	srclen = (unsigned int)ft_strlen(s);
	i = -1;
	if (start >= srclen)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *) malloc(len + 1);
	if (!sub)
		return (NULL);
	while (++i < len && start[s] && start < srclen)
		*(sub + i) = *(s + start + i);
	sub[i] = '\0';
	return (sub);
}

int	ft_strcmp(char *first, char *second)
{
	size_t	i;

	i = 0;
	while (first[i] && second[i] && first[i] == second[i])
			i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}
