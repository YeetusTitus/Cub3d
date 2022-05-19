#include "cub3d.h"

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

char	**get_map(char **argv)
{
	char	**map;
	char	*str;
	int		fd;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (get_map_size(argv) + 1));
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (is_char_ok(str) == 1)
	{
		free(str);
		str = get_next_line(fd);
	}
	while (is_char_ok(str) == 0)
	{
		map[i++] = ft_strndup(str, ft_strlen(str) - 1);
		free(str);
		str = get_next_line(fd);
	}
	map[i] = NULL;
	free(str);
	return (map);
}

t_data save_player_pos(t_data d)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (d.map[i])
	{
		while (d.map[i][j])
		{
			if (d.map[i][j] == 'N' || d.map[i][j] == 'S'
				|| d.map[i][j] == 'E' || d.map[i][j] == 'W')
			{
				d.pos[0] = i;
				d.pos[1] = j;
				d.orientation = d.map[i][j];
				d.map[i][j] = '0';
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (d);
}
