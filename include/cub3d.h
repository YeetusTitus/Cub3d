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

typedef struct s_data {
	int		pos[2];
	char	orientation;
	char	**map;
}	t_data;

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
char	*ft_substr_v2(char *s, int start, int len);
char	*cut_line(char **str, int pos);
char	*no_new_line(char **str);
char	*get_next_line(int fd);
int		ft_strlen_v2(char *str);
char	*ft_strjoin_v2(char *s1, char *s2);
char	*ft_strdup_v2(const char *s1);
int		ft_strchr_v2(char *s, char c);
char	*ft_memmove_v2(char *dst, char *src, int len);

//parsing map
int		get_map_size(char **argv);
char	**get_map(char **argv);
t_data	save_player_pos(t_data d);

//check map
int 	check_nb_player(char **map);
int 	check_char(char **map);
int		check_wall(char **map);
void    check_map(char **map);

// parsing utils
int		is_char_ok(char *str);
char	**erase_whitespace(char **map);
int		skip_whitespace(char *str);
void	free_char_arr(char **map);

#endif