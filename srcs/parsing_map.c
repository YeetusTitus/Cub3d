/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:45:17 by ktroude           #+#    #+#             */
/*   Updated: 2022/06/03 20:15:43 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_file_size(char *argv)
{
	int		size;
	int		fd;
	char	*str;

	size = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	str = get_next_line(fd);
	while (str != NULL && str[0])
	{
		size++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (size);
}

int	verif_map(char **file, t_play *play, int i)
{
	int		im;

	while (space_line(file[i], ft_strlen(file[i])))
		i++;
	im = i;
	play->nbplayer = 0;
	play->lenght = 0;
	while (file[i] != NULL)
	{
		if (closed_room(file, play, i))
			return (1);
		if (ft_strlen(file[i]) > play->lenght)
			play->lenght = ft_strlen(file[i]);
		play->height++;
		i++;
	}
	if (play->nbplayer != 1)
	{
		play->error = 'P';
		return (1);
	}
	get_map(file, play, im);
	return (0);
}

void	get_map(char **file, t_play *play, int i)
{
	int	j;
	int	k;

	j = -1;
	play->map = malloc(sizeof(char *) * (play->height + 1));
	while (file[i])
	{
		play->map[++j] = (char *)malloc((sizeof(char) * play->lenght) + 1);
		k = -1;
		while (++k < play->lenght)
		{
			if (k < ft_strlen(file[i]) && file[i][k] != ' ')
				play->map[j][k] = file[i][k];
			else
				play->map[j][k] = '1';
			save_player_pos(play, j, k);
		}
		play->map[j][k] = 0;
		i++;
	}
	play->map[++j] = NULL;
}

//a changer
void	save_player_pos(t_play *play, int x, int y)
{
	if (play->map[x][y] == 'N' || play->map[x][y] == 'S'
		|| play->map[x][y] == 'E' || play->map[x][y] == 'W')
	{
		play->posx = y + 0.5;
		play->posy = x + 0.5;
		get_dir_x_y(play->map[x][y], play);
		get_plane(play->map[x][y], play);
		play->map[x][y] = '0';
	}
}

void	get_dir_x_y(char c, t_play *p)
{
	if (c == 'N')
	{
		p->dirx = 0;
		p->diry = 1;
	}
	if (c == 'S')
	{
		p->dirx = 0;
		p->diry = -1;
	}
	if (c == 'E')
	{
		p->dirx = 1;
		p->diry = 0;
	}
	if (c == 'W')
	{
		p->dirx = -1;
		p->diry = 0;
	}
}
