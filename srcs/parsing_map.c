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

t_data	get_map(char **argv)
{
	t_data	d;
	char	*str;
	int		fd;
	int		i;

	i = 0;
	d.map = malloc(sizeof(char *) * (get_map_size(argv) + 1));
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (is_char_ok(str) == 1)
	{
		free(str);
		str = get_next_line(fd);
	}
	while (is_char_ok(str) == 0)
	{
		d.map[i++] = ft_strndup(str, ft_strlen(str) - 1);
		free(str);
		str = get_next_line(fd);
	}
	d.map[i] = NULL;
	free(str);
	return (d);
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