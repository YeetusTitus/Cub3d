/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:08:43 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/30 16:31:39 by jforner          ###   ########.fr       */
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

// void	save_player_pos(t_map *map)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (map->map[i])
// 	{
// 		while (map->map[i][j])
// 		{
// 			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
// 				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
// 			{
// 				map->play.x = i;
// 				map->play.y = j;
// 				map->play.degre = map->map[i][j];
// 				map->map[i][j] = '0';
// 			}
// 			j++;
// 		}
// 		i++;
// 		j = 0;
// 	}
// }
// 
// t_data	get_same_size_all_lines(t_data d)
// {
// 	int	i;
// 	int	size;
// 
// 	i = 0;
// 	size = 0;
// 	while (d.map[i])
// 	{
// 		if (ft_strlen_v2(d.map[i]) > size)
// 			size = ft_strlen_v2(d.map[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (d.map[i])
// 	{
// 		if (ft_strlen_v2(d.map[i]) < size)
// 			d.map[i] = ft_strjoin_v2(d.map[i], "1");
// 		if (ft_strlen_v2(d.map[i]) == size)
// 			i++;
// 	}
// 	return (d);
// }

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
		}
		map->map[j][k] = 0;
		i++;
	}
	map->map[++j] = NULL;
}
