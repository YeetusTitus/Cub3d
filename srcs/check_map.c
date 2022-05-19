#include "cub3d.h"

int	check_nb_player(char **map)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	j = 0;
	p = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				p++;
			j++;
		}
		i++;
		j = 0;
	}
	if (p != 1)
		return (1);
	return (0);
}

int	check_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			while (map[i][j] == ' ' || map[i][j] == '	')
				j++;
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j]
				!= 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	check_wall(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = skip_whitespace(map[i]);
	while (map[i][j++])
		if (map[i][j] != '1' || map[i][j] == ' ')
			return (1);
	while (map[++i + 1])
	{
		j = skip_whitespace(map[i]);
		if (map[i][j] != '1')
			return (1);
		while (map[i][j])
		{
			if (map[i][j] == '0' && ((map[i - 1][j] != '1'
			|| map[i - 1][j] != '0') || (map[i + 1][j] != '1'
			|| map[i + 1][j] != '0') || j > ft_strlen_v2(map[i - 1])
			|| j > ft_strlen_v2(map[i + 1])))
				return (1);
			j++;
		}
	}
	return (0);
}

void	check_map(char **map)
{
	int	j;

	j = 0;
	j += check_nb_player(map);
//	j += check_wall(map);
	j += check_char(map);
	if (j != 0)
	{
		ft_putstr_fd("Invalid Map\n", 1);
		free_char_arr(map);
		exit(1);
	}
}
