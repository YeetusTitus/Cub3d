/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:22:11 by jforner           #+#    #+#             */
/*   Updated: 2022/05/19 16:29:27 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_puterror(int argc, t_map *map, char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (argc != 2)
		ft_putstr_fd("Put the path of one map on the argument !\n", 2);
	else if (map->error != '0')
	{
		if (map->error == '1')
			ft_putstr_fd("The map is not close !\n", 2);
		if (map->error == 'P')
			ft_putstr_fd("The number of player is not correct !\n", 2);
		if (map->error == 'O')
			ft_putstr_fd("Wrong character in a map\n", 2);
		if (map->error == 'N')
			ft_putstr_fd("No character in the file\n", 2);
		if (map->error == 'F')
			ft_putstr_fd("It's not a .cub file\n", 2);
	}
	else
		ft_putstr_fd(strerror(errno), 2);
	return (1);
}

int	fileverif(t_map *map, char *str, int fd)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u'
			&& str[i + 3] == 'b' && str[i + 4] == '\0')
			return (0);
	}
	map->error = 'm';
	close(fd);
	return (1);
}
