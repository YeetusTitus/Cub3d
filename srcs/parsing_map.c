/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:08:43 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/24 18:26:00 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_map_size(char **argv)
{
	int		size;
	int		fd;
	char	*str;

	size = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	str = get_next_line(fd);
	close(fd);
	while (is_char_ok(str) == 1)
	{
		free(str);
		str = get_next_line(fd);
	}
	while (is_char_ok(str) == 0)
	{
		size++;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (size);
}

void	get_map(char **argv, t_map *map)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	map->map = malloc(sizeof(char *) * (get_map_size(argv) + 1));
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (is_char_ok(str) == 1)
	{
		free(str);
		str = get_next_line(fd);
	}
	while (is_char_ok(str) == 0)
	{
		map->map[i++] = ft_strndup(str, ft_strlen(str) - 1);
		free(str);
		str = get_next_line(fd);
	}
	map->map[i] = NULL;
	free(str);
}

void	save_player_pos(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->play.x = i;
				map->play.y = j;
				map->play.degre = map->map[i][j];
				map->map[i][j] = '0';
			}
			j++;
		}
		i++;
		j = 0;
	}
}

t_data	get_same_size_all_lines(t_data d)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (d.map[i])
	{
		if (ft_strlen_v2(d.map[i]) > size)
			size = ft_strlen_v2(d.map[i]);
		i++;
	}
	i = 0;
	while (d.map[i])
	{
		if (ft_strlen_v2(d.map[i]) < size)
			d.map[i] = ft_strjoin_v2(d.map[i], "1");
		if (ft_strlen_v2(d.map[i]) == size)
			i++;
	}
	return (d);
}