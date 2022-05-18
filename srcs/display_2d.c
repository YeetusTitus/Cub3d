/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:50:48 by jforner           #+#    #+#             */
/*   Updated: 2022/05/17 15:50:56 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// à changer
void	display_minimap(t_map *map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1024)
	{
		j = -1;
		while (++j < 520)
			mlx_pixel_put(map->mlx, map->win, i, j, 0x00616570);
	}
	draw_player(map, x, y, 0x00FFFF00);
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
			mlx_pixel_put(map->mlx, map->win, i, j, color);
	}
	printf("big chungs = %d unganda = %d\n", i, j);
}
