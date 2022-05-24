/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:50:48 by jforner           #+#    #+#             */
/*   Updated: 2022/05/23 15:30:03 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// à changer
void	display_minimap(t_map *map, int x, int y)
{
	int	i;
	int	j;

	i = 99;
	while (++i < 260)
	{
		j = 302;
		while (++j < 462)
			mlx_pixel_put(map->mlx, map->win, i, j, 0xDDF105AA);
	}
	draw_player(map, x, y, 0x00FFFF00);
}

void	draw_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1024)
	{
		j = -1;
		while (++j < 512)
		{
			if (i % 32 == 0 || j % 32 == 0)
				mlx_pixel_put(map->mlx, map->win, i, j, 0x00616570);
			else if (map->lenght > i / 8 && map->height > i / 8
				&& map->map[i / 8][j / 8] == 1)
				mlx_pixel_put(map->mlx, map->win, i, j, 0x00FFFFFF);
		}
	}
}

void	draw_player(t_map *map, int x, int y, int color)
{
	int	i;
	int	j;

	i = x - 3;
	while (++i < (x + 3))
	{
		j = y - 3;
		while (++j < (y + 3))
		{
			if ((i % 32 == 0 || j % 32 == 0) && !color)
				mlx_pixel_put(map->mlx, map->win, i, j, 0x00616570);
			else
				mlx_pixel_put(map->mlx, map->win, i, j, color);
		}
	}
	printf("big chungs = %d unganda = %d\n", i, j);
}
