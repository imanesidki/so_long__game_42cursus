/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:53:54 by isidki            #+#    #+#             */
/*   Updated: 2023/05/12 20:04:34 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define D 2
# define W 13
# define S 1
# define A 0
# define ESC 53

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
	void	*img_e_c;
	void	*img_e_o;
	void	*img_p_l;
	void	*img_p_r;
	void	*mlx_win;
	int		x;
	int		y;
	int		img_width;
	int		img_height;
	int		nbr_collectb;
	int		x_player;
	int		y_player;
	int		moves;
	char	**lines;
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
char	**remplir_lines_parsing(char *file, int size);
void	position_player(char **lines, t_data *data);
void	free_lines(char **lines);
void	ft_putnbr(int nb);
/*******************mlx*******************/
/***************************************************/
void	ft_xpm_image(t_data *data);
void	ft_xpm_image2(t_data *data);
void	ft_image_to_win1(t_data *data, int i, int j);
void	ft_image_to_win2(t_data *data, int i, int j);
void	ft_put_img(t_data *data);
void	ft_mlx(t_data *data);
int		ft_left(t_data *data);
int		ft_down(t_data *data);
int		ft_up(t_data *data);
int		ft_right(t_data *data);
int		ft_check(int key, void *param);
int		ft_open_door(t_data *data);
int		ft_close(void *param);
int		exit_player(t_data *data);
/***************************************************/

#endif
