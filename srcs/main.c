/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:27:27 by jforner           #+#    #+#             */
/*   Updated: 2022/05/17 18:06:12 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_map	map;

	(void)(argv);
	(void)(argc);
	map.play.x = 506;
	map.play.y = 203;
	map.play.degre = 3 * M_PI_2;
	// map.play.dx = round(cos(3 * M_PI_2) * 5);
	// map.play.dy = round(sin(3 * M_PI_2) * 5);
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, 1024, 512, "Cub3d");
	display_minimap(&map, map.play.x, map.play.y);
	// mlx_key_hook(map.win, move_on_win, &map);
	mlx_hook(map.win, 2, 1L << 0, move_on_win, &map);
	mlx_hook(map.win, 17, 1L << 2, red_cross, &map);
	mlx_loop(map.mlx);
	return (0);
}
