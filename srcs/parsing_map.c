/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:08:43 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/30 17:06:56 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	while (str[0])
	{
		size++;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	return (size);
}

int	verif_map(char **file, t_map *map, int i)
{
	int		im;

	while (space_line(file[i], ft_strlen(file[i])))
		i++;
	im = i;
	map->nbplayer = 0;
	map->lenght = 0;
	while (file[i] != NULL)
	{
		if (closed_room(file, map, i))
			return (1);
		if (ft_strlen(file[i]) > map->lenght)
			map->lenght = ft_strlen(file[i]);
		map->height++;
		i++;
	}
	if (map->nbplayer != 1)
	{
		map->error = 'P';
		return (1);
	}
	get_map(file, map, im);
	return (0);
}

void	get_map(char **file, t_map *map, int i)
{
	int	j;
	int	k;

	j = -1;
	map->map = malloc(sizeof(char *) * (map->height + 1));
	while (file[i])
	{
		map->map[++j] = (char *)malloc((sizeof(char) * map->lenght) + 1);
		k = -1;
		while (++k < map->lenght)
		{
			if (k < ft_strlen(file[i]) && file[i][k] != ' ')
				map->map[j][k] = file[i][k];
			else
				map->map[j][k] = '1';
			save_player_pos(map, j, k);
		}
		map->map[j][k] = 0;
		i++;
	}
	map->map[++j] = NULL;
}

void	save_player_pos(t_map *map, int x, int y)
{
	if (map->map[x][y] == 'N' || map->map[x][y] == 'S'
		|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
	{
		map->play.x = x;
		map->play.y = y;
		map->map[x][y] = '0';
		if (map->map[x][y] == 'E')
			map->play.degre = 0;
		if (map->map[x][y] == 'N')
			map->play.degre = M_PI_2;
		if (map->map[x][y] == 'W')
			map->play.degre = M_PI;
		if (map->map[x][y] == 'S')
			map->play.degre = 3 * M_PI_2;
	}
}
