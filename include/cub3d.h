/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:58:44 by jforner           #+#    #+#             */
/*   Updated: 2022/05/31 15:49:31 by jforner          ###   ########.fr       */
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

typedef struct s_play {
	double	posx; // start pos x
	double	posy; // start pos y
	double	dirx; //initial direction vecteurs
	double	diry; //initial direction vecteurs
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		color;
	double	frametime;
	double	movespeed;
	double	rotspeed;
	double	olddirx;
	double	oldplanx;
	int		keyhook;
	int		x;
	char	**map;

	t_color	*texture;
	char	error;
	int		lenght;
	int		height;
	int		nbplayer;




	void	*image_pointer;
	void	*mlx;
	void	*win;
	void	*my_image_data;
}	t_play;





//display_2d
void	display_minimap(t_play *play, int x, int y);
void	draw_player(t_play *play, int x, int y, int color);
void	draw_map(t_play *play);

//event
int		move_on_win(int keycode, t_play *play);
void	change_play(t_play *play, int kc);
int		wclose(t_play *play);
int		red_cross(int keycode, int x, int y, t_play *play);
int		display_mmap(int keycode, t_play *play);

//error
int		fileverif(t_play *play, char *str, int fd, char c);
int		ft_puterror(int argc, t_play *play);

//gnl
char	*get_next_line(int fd);
char	*ft_strjoin_v2(char *s1, char const *s2);
int		checkchr(const char *str, char ch);

//utils1
int		space_line(char	*str, int lenght);
int		tablen(char **tabl);
int		ft_malloc_error(char **tab, int size);
void	delete_screen(t_play *play);
int		is_space(char c);

//utils 2
void	freedom(t_play *play);

//parsing
int		map_parsing(t_play *play, char **file);
int		parsing(t_play *play, char **argv);
int		create_color(int *array, char *parse);
int		options_switch2(t_play *play, char **parse, int direction[6]);
int		options_switch(t_play *play, char **parse);

//parsing map
int		verif_map(char **file, t_play *play, int i);
int		get_file_size(char *argv);
void	get_map(char **file, t_play *play, int i);
void	save_player_pos(t_play *play, int x, int y);
void	get_dir_x_y(char c, t_play *p);

//parsing_utils
int		closed_room(char **file, t_play *play, int j);
void	trick_room(char **f, t_play *play, int j, int i);
int		is_char_ok(char *str);
char	**get_file(t_play *play, char *argv);

#endif