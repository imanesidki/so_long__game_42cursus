/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:53:54 by isidki            #+#    #+#             */
/*   Updated: 2023/05/08 01:07:56 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

typedef struct data
{
	void	*mlx_ptr;
	void	*img_c;
	void	*img_0;
	void	*img_w;
	void	*img_e;
	void	*img_p;
	void	*mlx_win;
	int		x;
	int		y;
	int		nbr_collectb;
	int		x_player;
	int		y_player;
}	t_data;

/*******************get_next_line*******************/
/***************************************************/
char	*ft_strchr(char *string, int c);
char	*ft_strjoin_strings(char *s1, char *s2);
char	*ft_substrs(char *s, unsigned int start, int len);
int		ft_strcmp(char *first, char *second);
char	*read_buff(int fd, char *hold);
char	*update(char *hold);
char	*mygetline(char *hold);
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strdup(char *source);
/*******************parsing*******************/
/***************************************************/
void	parsing_map(char **lines, t_data *data);
int		valid_path(char **lines, int x, int y, int c);
void	exit_error(char *str);
void	check_file_name(char *v);
int		ft_open(char *file);
void	check_wall(char **lines, t_data *data);
void	check_rectangular(char **lines, t_data *data);
void	check_number_characters(char **lines, t_data *data);
int		nbr_lines(char *av, t_data *data);
void	ft_initialize(t_data *data);
char	**remplir_lines(char *file, int size);
char	**remplir_lines_parsing(char *file, int size);
char	*ft_strdup_new(char *source);
void	position_player(char **lines, t_data *data);
void	free_lines(char **lines);
/*******************mlx*******************/
/***************************************************/
void	ft_xpm_image(t_data *data);
void	ft_image_to_win1(char **lines, t_data *data, int i, int j);
void	ft_image_to_win2(char **lines, t_data *data, int i, int j);
void	ft_put_img(char **lines, t_data *data);
void	ft_mlx(char **lines, t_data *data);
/***************************************************/

#endif
