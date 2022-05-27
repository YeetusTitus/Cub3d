/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:49:34 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/27 15:51:17 by jforner          ###   ########.fr       */
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
		if (ft_strlen_v2(str) < 3)
			return (1);
		if (str[i] != ' ' && str[i] != '	' && str[i] != '1' && str[i] != '0'
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != 3)
			return (1);
		i++;
	}
	return (0);
}

int	closed_room(char **file, t_map *map, int j)
{
	static int	countline = 0;
	int			i;

	i = -1;
	while (file[j][++i])
	{
		if ((file[j + 1] == NULL || !countline)
			&& file[j][i] != '1' && file[j][i] != '\t' && file[j][i] != ' ')
			map->error = '1';
		else if (file[j + 1] != NULL && countline)
		{
			if ((is_space(str[i]) || file[j][i + 1] == '\0')
				&& file[j][i] != '1')
				map->error = '1';
			else if (i == 0 && file[j][i] != '\t' || file[j][i] != ' '
				&& file[j][i] != '1')
				map->error = '1';

		}
		if (map->error != '0')
			return (1);
	}
	countline++;
	return (0);
}

void	erase_whitespace(t_map *map)
{
	int	i;
	int	j;
	int	tab;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
				map->map[i][j] = '1';
			else if (map->map[i][j] == '\t')
			{
				tab = 4 - (j % 4);
				while (tab-- > 0)
					map->map[i][j] = '1';
			}
			j++;
		}
		i++;
	}
}

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	return (i);
}
