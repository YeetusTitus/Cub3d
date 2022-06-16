/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:58:44 by jforner           #+#    #+#             */
/*   Updated: 2022/06/16 15:56:03 by jforner          ###   ########.fr       */
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
# include "../mlx/mlx.h"

# define SCREENWIDTH 800
# define SCREENHEIGHT 400
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct s_disp {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_disp;

typedef struct s_color {
	int		floor;
	int		ceil;
}				t_color;

typedef struct s_keys {
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}				t_keys;

typedef struct s_play {
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
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
	double	movespeed;
	double	rotspeed;
	double	olddirx;
	double	oldplanx;
	char	**map;

	double	floorxwall;
	double	floorywall;
	double	distwall;
	double	distplayer;
	double	currentdist;
	double	weight;
	double	currentfloorx;
	double	currentfloory;
	int		floortexx;
	int		floortexy;
	double	wallx;
	int		texx;
	double	step;
	double	texpos;
	int		texy;
	int		buffer[SCREENHEIGHT][SCREENWIDTH];
	t_disp	text[6];

	t_color	*texture;
	t_keys	keys;
	char	error;
	int		lenght;
	int		height;
	int		nbplayer;
	int		mouse;
	int		xmouse;
	int		showmap;

	t_disp	disp;
	t_disp	hide;
	t_disp	mmap;

	void	*mlx;
	void	*win;
}	t_play;

//minimap
void	mmap_print(t_play *p, int show);
void	mmap_color(t_play *p, int i, int j, int coord[2]);
void	create_hide(t_play *p);

//error
int		fileverif(t_play *play, char *str, int fd, char c);
int		ft_puterror(int argc, t_play *play);

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
int		get_file_size(char *argv);
int		verif_map(char **file, t_play *play, int i);
void	get_map(char **file, t_play *play, int i);
void	save_player_pos(t_play *play, int x, int y);
void	get_dir_x_y(char c, t_play *p);

//parsing
int		create_color(int *array, char *parse);
int		options_switch2(t_play *play, char **parse, int direction[6]);
int		options_switch(t_play *play, char **parse);
int		param_parsing(t_play *play, char **file, int *i);
int		parsing(t_play *play, char **argv);

// parsing utils
int		is_char_ok(char *str);
void	trick_room(char **f, t_play *play, int j, int i);
int		closed_room(char **file, t_play *play, int j);
char	**get_file(t_play *play, char *argv);
void	get_plane(char c, t_play *play);

// raycasting
void	raycast_loop(t_play *p, int w, int h);
void	step_n_sidedist(t_play *p);
void	wall_size(t_play *p, int h);
void	write_color_in_buffer(t_play *p, int x, int h);
void	display_n_free_buffer(t_play *p, int h, int w);

// mouvements
int		move_up(t_play *p);
int		move_down(t_play *p);
int		rotate_left(t_play *p);
int		rotate_right(t_play *p);
int		readkeys(int keys, t_play *play);

//utils1
int		ft_malloc_error(char **tab, int size);
int		tablen(char **tabl);
int		space_line(char	*str, int lenght);
int		is_space(char c);

//utils2
void	freedom(t_play *play);
int		split_len2(char *str);
void	strlen2(char *str, int *k);
void	splitage2(char *str, char **tabl, int len);
char	**split_v2(char *str);

//utils 3
void	init_win(t_play *p);
int		get_data_color(int x, int y, t_disp disp);
void	ft_pixel_put(t_disp *display, int x, int y, int color);
void	get_floorwall(t_play *p, int h, int *y);

//event
int		red_cross(int keycode, int x, int y, t_play *play);
int		wclose(t_play *play);
int		move_left(t_play *p);
int		move_right(t_play *p);
int		mousing(int x, int y, t_play *play);

//event2
int		show_mouse(t_play *play);
int		show_mmmap(t_play *play);
int		readkeys2(int key, t_play *p);
int		display_loop(t_play *p);

//texndda
void	texture_floor_n_ceil(t_play *p, int h, int x);
void	texture_calcul(t_play *p, int h);
void	init_dda(t_play *p, int x, int w);
void	perform_dda(t_play *p);
void	load_texture(t_play *p);

#endif
