/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:46:36 by ktroude           #+#    #+#             */
/*   Updated: 2022/06/03 20:00:23 by jforner          ###   ########.fr       */
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
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0'
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != 3)
			return (1);
		i++;
	}
	return (0);
}

void	trick_room(char **f, t_play *play, int j, int i)
{
	if ((f[j][i + 1] == ' ' || f[j][i + 1] == '\n' || f[j][i + 1] == '\0')
		&& f[j][i] != '1' && f[j][i] != ' ')
		play->error = '1';
	if ((i > 0 && f[j][i - 1] == ' ') && f[j][i] != '1' && f[j][i] != ' ')
		play->error = '1';
	if (i == 0 && f[j][i + 1] != ' ' && f[j][i] != '1')
		play->error = '1';
	if ((f[j][i] == '0' || f[j][i] == 'E' || f[j][i] == 'N'
		|| f[j][i] == 'W' || f[j][i] == 'S')
			&& (i >= ft_strlen(f[j - 1]) || f[j - 1][i] == ' '))
		play->error = '1';
	if ((f[j][i] == '0' || f[j][i] == 'E' || f[j][i] == 'N'
		|| f[j][i] == 'W' || f[j][i] == 'S')
			&& (i >= ft_strlen(f[j + 1]) || f[j +1][i] == ' '))
		play->error = '1';
}

int	closed_room(char **file, t_play *play, int j)
{
	static int	countline = 0;
	int			i;

	i = -1;
	if (is_char_ok(file[j]))
		play->error = 'C';
	while (file[j][++i] != 0)
	{
		if (file[j][i] == 'E' || file[j][i] == 'N' || file[j][i] == 'W'
			|| file[j][i] == 'S')
			play->nbplayer++;
		if ((file[j + 1] == NULL || !countline)
			&& file[j][i] != '1' && file[j][i] != ' ')
			play->error = '1';
		else if (file[j + 1] != NULL && countline)
			trick_room(file, play, j, i);
		if (play->error != '0')
			return (1);
	}
	countline++;
	return (0);
}

char	**get_file(t_play *play, char *argv)
{
	int		i;
	int		fd;
	int		len;
	char	**file;

	i = -1;
	len = get_file_size(argv);
	if (!len)
	{
		play->error = 'N';
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
	file[i] = NULL;
	return (file);
}

void	get_plane(char c, t_play *play)
{
	if (c == 'W')
	{
		play->planex = 0;
		play->planey = 0.66;
	}
	if (c == 'N')
	{
		play->planex = 0.66;
		play->planey = 0;
	}
	if (c == 'E')
	{
		play->planex = 0;
		play->planey = -0.66;
	}
	if (c == 'S')
	{
		play->planex = -0.66;
		play->planey = 0;
	}
}
