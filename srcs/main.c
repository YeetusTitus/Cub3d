/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:27:27 by jforner           #+#    #+#             */
/*   Updated: 2022/05/18 16:28:42 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_data	d;
	t_play	*p;
	t_play	c;

	p = NULL;
	if (argc == 2)
	{
		d = get_map(argv);
		check_map(d.map);
		d = save_player_pos(d);
		d = erase_whitespace(d);
		d = get_same_size_all_lines(d);
		c = init_t_play(&d);
		p = &c;
		p->mlx = mlx_init();
		p->win = mlx_new_window(p->mlx, 400, 200, "Cub3d");
		raycast_loop(p, &d, 400, 200);
	}
}

/*	t_map	map;

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
	mlx_hook(map.win, 2, 1L << 0, move_on_win, &map);\
	mlx_key_hook(map.win, display_mmap, &map);
	mlx_hook(map.win, 17, 1L << 2, red_cross, &map);
	mlx_loop(map.mlx);
	return (0);

	*/
