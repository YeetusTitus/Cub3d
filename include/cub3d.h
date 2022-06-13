/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:58:44 by jforner           #+#    #+#             */
/*   Updated: 2022/06/06 18:43:45 by jforner          ###   ########.fr       */
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


#define screenwidth 400
#define screenheight 200
//#define texwidth 64
//#define texheight 64



typedef struct s_disp {
	unsigned int	color;
	int				tab[64 * 64 + 64];
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_disp;

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

typedef struct s_color {
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		floor;
	int		ceil;
}				t_color;

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
///// variable texture sol / plafond
    float   raydirx0;
    float   raydiry0;
    float   raydirx1;
    float   raydiry1;
    int     p;
    float   posz;
    float   rowdistance;
    float   floorstepx;
    float   floorstepy;
    float   floorx;
    float   floory;
    int     cellx;
    int     celly;
    int     tx;
    int     ty;
    int     floortexture;
    int     ceilingtexture;
    double  floorxwall;
    double  floorywall;
    double  distwall;
    double  distplayer;
    double  currentdist;
    double  weight;
    double  currentfloorx;
    double  currentfloory;
    int     floortexx;
    int     floortexy;
/////
	double	wallx;
	int		texx;
	double	step;
	double	texpos;
	int		texy;
	int		buffer[200][400];
	
	t_disp	text[6];
	
	t_color	*texture;
	char	error;
	int		lenght;
	int		height;
	int		nbplayer;
	int		xmouse;

	t_disp	disp;


	void	*image_pointer;
	void	*mlx;
	void	*win;
	void	*my_image_data;
}	t_play;

typedef struct s_data {
	int		pos[2];
	char	orientation;
	char	**map;
}	t_data;

//display_2d
void	display_minimap(t_map *map, int x, int y);
void	draw_player(t_map *map, int x, int y, int color);

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

//check map ?
// int 	check_nb_player(char **map);
// int 	check_char(char **map);
// int		check_wall(char **map);
// void    check_map(char **map);

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
// t_play	init_t_play(t_data *d);
// void	get_dir_x_y(char c, t_play *p);
void	raycast_loop(t_play *p, int w, int h);
void	verline(int x, t_play *p);
int		readkeys(int keys, t_play *play);
t_play	*get_step_n_sidedist_incr(t_play *p);
t_play	*get_hit(t_play *p);

// mouvements
int		move_up(t_play *p);
int		move_down(t_play *p);
int		rotate_left(t_play *p);
int		rotate_right(t_play *p);

//utils1
int		ft_malloc_error(char **tab, int size);
int		tablen(char **tabl);
int		space_line(char	*str, int lenght);
void	delete_screen(t_play *play);
int		is_space(char c);

//utils2
void	freedom(t_play *play);
int		split_len2(char *str);
void	strlen2(char *str, int *k);
void	splitage2(char *str, char **tabl, int len);
char	**split_v2(char *str);

//event
int		red_cross(int keycode, int x, int y, t_play *play);
int		wclose(t_play *play);
int		move_left(t_play *p);
int		move_right(t_play *p);
int		mousing(int x, int y, t_play *play);

//event2
int		show_mouse(void);
void	ft_pixel_put(t_disp *display, int x, int y, int color);


//texture
int	get_data_color(int x, int y, int i,  t_play *p);
t_play	*load_texture(t_play *p);
t_play	*init_t_play(t_play *p);
t_play	*init_DDA(t_play *p, int x, int w);
t_play	*step_n_sidedist(t_play *p);
t_play	*perform_DDA(t_play *p);
t_play	*wall_size(t_play *p, int h);
t_play	*texture_calcul(t_play *p, int texwidth, int texheight, int h);
t_play	*write_color_in_buffer(t_play *p, int texheight, int texwidth, int x);
t_play	*display_n_free_buffer(t_play *p, int h, int w);
t_play  *texture_floor_n_ceil(t_play *p, int h, int x, int texheight, int texwidth);



#endif