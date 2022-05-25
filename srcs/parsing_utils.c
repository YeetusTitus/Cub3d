/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:46:36 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/25 18:46:38 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			&& str[i] != 'W' && str[i] != '\n' && str[i] != 3)
			return (1);
		i++;
	}
	return (0);
}

t_data	erase_whitespace(t_data d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d.map[i])
	{
		while (d.map[i][j])
		{
			if (d.map[i][j] == '	' || d.map[i][j] == ' ')
				d.map[i][j] = '1';
			j++;
		}
		j = 0;
		i++;
	}
	return (d);
}

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '	' || str[i] == ' ')
		i++;
	return (i);
}

void	free_char_arr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map[i]);
	free(map);
}
