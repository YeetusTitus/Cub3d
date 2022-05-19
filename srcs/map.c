/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:23:29 by jforner           #+#    #+#             */
/*   Updated: 2022/05/18 13:52:24 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//M_PI == pi
// M_PI_2 == pi / 2

int	map_parsing(t_map *map, int fd)
{
	return (0);
}

int	parsing(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	map->error == '0';
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || !fileverif(map, argv[1], fd))
		return (1);
	line = get_next_line(fd);
	if (line == NULL)
	{
		map->error = 'N';
		return (1);
	}
	if (map_parsing(map, fd))
		return (1);
	return (0);
}
