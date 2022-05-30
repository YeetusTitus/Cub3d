/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:58:44 by jforner           #+#    #+#             */
/*   Updated: 2022/05/30 17:04:26 by jforner          ###   ########.fr       */
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

typedef struct s_color {
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		floor;
	int		ceil;
}				t_color;

typedef struct s_map {
	int				lenght;
	int				height;
	int				nbplayer;
	char			**minimap;
	char			**map;
	char			error;
	int				fd;
	void			*mlx;
	void			*win;
	t_player		play;
	t_color			color;
}				t_map;

//display_2d
void	display_minimap(t_map *map, int x, int y);
void	draw_player(t_map *map, int x, int y, int color);
void	draw_map(t_map *map);

//event
int		move_on_win(int keycode, t_map *map);
void	change_play(t_map *map, int kc);
int		wclose(t_map *map);
int		red_cross(int keycode, int x, int y, t_map *map);
int		display_mmap(int keycode, t_map *map);

//error
int		fileverif(t_map *map, char *str, int fd, char c);
int		ft_puterror(int argc, t_map *map);

//gnl
char	*get_next_line(int fd);
char	*ft_strjoin_v2(char *s1, char const *s2);
int		checkchr(const char *str, char ch);

//utils1
int		space_line(char	*str, int lenght);
int		tablen(char **tabl);
int		ft_malloc_error(char **tab, int size);
void	delete_screen(t_map *map);
int		is_space(char c);

//utils 2
void	freedom(t_map *map);

//parsing
int		map_parsing(t_map *map, char **file);
int		parsing(t_map *map, char **argv);
int		create_color(int *array, char *parse);
int		options_switch2(t_map *map, char **parse, int direction[6]);
int		options_switch(t_map *map, char **parse);

//parsing map
int		verif_map(char **file, t_map *map, int i);
int		get_file_size(char *argv);
void	get_map(char **file, t_map *map, int i);
void	save_player_pos(t_map *map, int x, int y);

//parsing_utils
int		closed_room(char **file, t_map *map, int j);
void	trick_room(char **f, t_map *map, int j, int i);
int		is_char_ok(char *str);
char	**get_file(t_map *map, char *argv);

#endif