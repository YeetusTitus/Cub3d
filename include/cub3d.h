/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:58:44 by jforner           #+#    #+#             */
/*   Updated: 2022/05/18 17:14:04 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_player {
	int		x;
	int		y;
	double	dx;
	double	dy;
	double	degre;
	int		spe;
}				t_player;

typedef struct s_map {
	int				lenght;
	int				height;
	char			**minimap;
	char			**map;
	char			error;
	int				fd;
	void			*mlx;
	void			*win;
	t_player		play;
}				t_map;

//display_2d
void	display_minimap(t_map *map, int x, int y);
void	draw_player(t_map *map, int x, int y, int color);

//event
int		move_on_win(int keycode, t_map *map);
void	change_play(t_map *map, int kc);
int		wclose(t_map *map);
int		red_cross(int keycode, int x, int y, t_map *map);
int		display_mmap(int keycode, t_map *map);

//error
int		fileverif(t_map *map, char *str, int fd);
int		ft_puterror(int argc, t_map *map, char *str);

//gnl
char	*get_next_line(int fd);
char	*ft_strjoin_v2(char const *s1, char const *s2);
int		checkchr(const char *str, char ch);
#endif