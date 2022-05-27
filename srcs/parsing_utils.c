/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:49:34 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/27 23:21:50 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_char_ok(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0'
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != 3)
			return (1);
		i++;
	}
	return (0);
}

void	trick_room(char **f, t_map *map, int j, int i)
{
	if ((f[j][i + 1] == ' ' || f[j][i + 1] == '\n' || f[j][i + 1] == '\0')
		&& f[j][i] != '1' && f[j][i + 1] != ' ')
		map->error = '1';
	// printf("trick 0 = %c\t j = %d\t i = %d\n", map->error, j, i);
	if ((i > 0 && f[j][i + 1] == ' ') && f[j][i] != '1' && f[j][i + 1] != ' ')
		map->error = '1';
	// printf("trick 1 = %c\t j = %d\t i = %d\n", map->error, j, i);
	if (i == 0 && f[j][i + 1] != ' ' && f[j][i] != '1')
		map->error = '1';
	// printf("trick 2 = %c\t j = %d\t i = %d\n", map->error, j, i);
	if ((f[j][i] == '0' || f[j][i] == 'E' || f[j][i] == 'N'
		|| f[j][i] == 'W' || f[j][i] == 'S')
			&& (i >= ft_strlen(f[j - 1]) || f[j - 1][i] == ' '))
		map->error = '1';
	// printf("trick 3 = %c\t j = %d\t i = %d\n", map->error, j, i);
	if ((f[j][i] == '0' || f[j][i] == 'E' || f[j][i] == 'N'
		|| f[j][i] == 'W' || f[j][i] == 'S')
			&& (i >= ft_strlen(f[j + 1]) || f[j +1][i] == ' '))
		map->error = '1';
	// printf("trick 4 = %c\t j = %d\t i = %d\n", map->error, j, i);
}

int	closed_room(char **file, t_map *map, int j)
{
	static int	countline = 0;
	int			i;

	i = -1;
	if (is_char_ok(file[j]))
		map->error = 'C';
	while (file[j][++i] != 0)
	{
		if (i == 0)
			printf("%d!\n", file[j][i]);
		if (file[j][i] == 'E' || file[j][i] == 'N' || file[j][i] == 'W'
			|| file[j][i] == 'S')
			map->nbplayer++;
		if ((file[j + 1] == NULL || !countline)
			&& file[j][i] != '1' && file[j][i] != ' ')
			map->error = '1';
		else if (file[j + 1] != NULL && countline)
			trick_room(file, map, j, i);
		if (map->error != '0')
			return (1);
	}
	printf("\n");
	countline++;
	return (0);
}

void	erase_whitespace(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
				map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

char	**get_file(t_map *map, char *argv)
{
	int		i;
	int		fd;
	int		len;
	char	**file;

	i = -1;
	len = get_file_size(argv);
	if (!len)
	{
		map->error = 'N';
		return (NULL);
	}
	file = malloc((sizeof(char *) * len) + 1);
	fd = open(argv, O_RDONLY);
	while (++i < len)
	{
		file[i] = get_next_line(fd);
		file[i][ft_strlen(file[i]) - 1] = 0;
	}
	close(fd);
	return (file);
}
