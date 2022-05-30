/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:12:10 by jforner           #+#    #+#             */
/*   Updated: 2022/05/30 16:04:39 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_malloc_error(char **tab, int size)
{
	while (size-- > 0)
		free(tab[size]);
	free(tab);
	return (1);
}

int	tablen(char **tabl)
{
	id_t	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

int	space_line(char	*str, int lenght)
{
	int	i;

	i = -1;
	while (str[++i] && i < lenght)
	{
		if (is_space(str[i]))
			return (0);
	}
	return (1);
}

void	delete_screen(t_map *map)
{
	mlx_destroy_image(map->mlx, map->color.east);
	mlx_destroy_image(map->mlx, map->color.north);
	mlx_destroy_image(map->mlx, map->color.west);
	mlx_destroy_image(map->mlx, map->color.south);
}

int	is_space(char c)
{
	if ((c < 7 || c > 13) && !(c == ' '))
		return (1);
	return (0);
}
// void	freedom(t_map *map)
// {
// }
