/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:02:42 by isidki            #+#    #+#             */
/*   Updated: 2023/05/31 05:45:17 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../src/so_long.h"

/*******************mlx*****************************/
void	ft_mlx_bonus(t_data *data);
void	ft_xpm_enemy_frames(t_data *data);
void	ft_image_to_win_bonus(t_data *data,int i,int j);
int		ft_check_bonus(int key, void *param);
int		ft_frame(void *param);
/*******************mlx_utils***********************/
char	*ft_strcat(char *dest, char *src);
char	*ft_itoa(int value, char *str);
/***************************************************/

#endif
