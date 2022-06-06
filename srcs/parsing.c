/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:23:29 by jforner           #+#    #+#             */
/*   Updated: 2022/06/03 21:12:38 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	create_color(int *array, char *parse)
{
	char	**color;
	int		i;

	color = ft_split(parse, ',');
	i = -1;
	while (++i < 3)
	{
		if (tablen(color) != 3 || ft_atoi(color[i]) > 255
			|| ft_atoi(color[i]) < 0)
			return (ft_malloc_error(color, tablen(color)));
	}
	*array = (ft_atoi(color[0]) * pow(16, 4))
		+ (ft_atoi(color[1]) * pow(16, 2)) + (ft_atoi(color[2]));
	ft_malloc_error(color, tablen(color));
	return (0);
}

int	options_switch2(t_play *play, char **parse, int direction[6])
{
	int			iw;
	int			ih;
	void		*test;

	test = mlx_xpm_file_to_image(play->mlx, parse[1], &iw, &ih);
	if (test == NULL)
		return (1);
	if (!ft_strncmp(parse[0], "WE", ft_strlen(parse[0])) && direction[2]--)
		play->texture->west = test;
	else if (!ft_strncmp(parse[0], "NO", ft_strlen(parse[0])) && direction[3]--)
		play->texture->north = test;
	else if (!ft_strncmp(parse[0], "EA", ft_strlen(parse[0])) && direction[0]--)
		play->texture->east = test;
	else if (!ft_strncmp(parse[0], "SO", ft_strlen(parse[0])) && direction[1]--)
		play->texture->south = test;
	else
		return (1);
	return (0);
}

int	options_switch(t_play *play, char **parse)
{
	static int	direction[6] = {1, 1, 1, 1, 1, 1};
	int			fd;

	if (ft_strlen(parse[0]) == 2)
	{
		fd = open(parse[1], O_RDONLY);
		if (fd < 0 || fileverif(play, parse[1], fd, 'x'))
			return (1);
		close(fd);
	}
	if (!ft_strncmp(parse[0], "C", ft_strlen(parse[0])) && direction[4])
	{
		if (create_color(&(play->texture->ceil), parse[1]) || --direction[4])
			return (1);
	}
	else if (!ft_strncmp(parse[0], "F", ft_strlen(parse[0])) && direction[5])
	{
		if (create_color(&(play->texture->floor), parse[1]) || --direction[5])
			return (1);
	}
	else if (options_switch2(play, parse, direction))
		return (1);
	return (0);
}

int	param_parsing(t_play *play, char **file, int *i)
{
	char	**parse;
	int		count;

	count = 6;
	*i = -1;
	while (file[++(*i)] != NULL)
	{
		if (!space_line(file[*i], ft_strlen(file[*i])))
		{
			parse = split_v2(file[*i]);
			if (tablen(parse) != 2 || options_switch(play, parse))
			{
				play->error = 'I';
				return (ft_malloc_error(parse, tablen(parse)));
			}
			count--;
			ft_malloc_error(parse, tablen(parse));
			if (count == 0)
				break ;
		}
	}
	if (count > 0)
		play->error = 'O';
	return (count);
}

int	parsing(t_play *play, char **argv)
{
	int		fd;
	char	**file;
	int		i;

	play->error = '0';
	play->map = NULL;
	play->texture = (t_color *)malloc(sizeof(t_color));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || fileverif(play, argv[1], fd, 'c'))
		return (1);
	close(fd);
	file = get_file(play, argv[1]);
	if (file == NULL)
		return (1);
	if (param_parsing(play, file, &i) || verif_map(file, play, i + 1))
	{
		ft_malloc_error(file, tablen(file));
		return (1);
	}
	ft_malloc_error(file, tablen(file));
	return (0);
}
