/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:57:09 by jforner           #+#    #+#             */
/*   Updated: 2022/05/17 18:04:57 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	red_cross(int keycode, int x, int y, t_map *map)
{
	(void)keycode;
	(void)x;
	(void)y;
	(void)map;
	exit(EXIT_SUCCESS);
}

int	wclose(t_map *map)
{
	mlx_destroy_window(map->mlx, map->win);
	exit(EXIT_SUCCESS);
	return (1);
}

void	change_play(t_map *map, int kc)
{
	int	tempx;
	int	tempy;

	tempx = map->play.x;
	tempy = map->play.y;
	if (kc == 13)
	{
		map->play.x += cos(map->play.degre) * 5;
		map->play.y += sin(map->play.degre) * 5;
	}
	if (kc == 2)
	{
		map->play.x += cos(map->play.degre + M_PI_2) * 5;
		map->play.y += sin(map->play.degre + M_PI_2) * 5;
	}
	if (kc == 0)
	{
		map->play.x -= cos(map->play.degre + M_PI_2) * 5;
		map->play.y -= sin(map->play.degre + M_PI_2) * 5;
	}
	if (kc == 1)
	{
		map->play.x -= cos(map->play.degre) * 5;
		map->play.y -= sin(map->play.degre) * 5;
	}
	draw_player(map, tempx, tempy, 0x00616570);
	draw_player(map, map->play.x, map->play.y, 0x00FFFF00);
}

int	move_on_win(int keycode, t_map *map)
{
	if (keycode == 53)
		wclose(map);
	if (!keycode || keycode == 1 || keycode == 2 || keycode == 13)
		change_play(map, keycode);
	if (keycode == 123)
	{
		map->play.degre -= 0.1;
		if (map->play.degre < 0)
			map->play.degre += 2 * M_PI;
		// map->play.dx = cos(map->play.degre);
		// map->play.dy = sin(map->play.degre);
		// printf("chaka = %f laka = %f\n", map->play.dx, map->play.dy);
	}
	if (keycode == 124)
	{
		map->play.degre += 0.1;
		if (map->play.degre > 2 * M_PI)
			map->play.degre -= 2 * M_PI;
		// map->play.dx = cos(map->play.degre);
		// map->play.dy = sin(map->play.degre);
		// printf("chaka = %f laka = %f\n", map->play.dx, map->play.dy);
	}
	return (1);
}
