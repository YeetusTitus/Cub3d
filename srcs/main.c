/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:27:27 by jforner           #+#    #+#             */
/*   Updated: 2022/06/13 13:55:19 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	// t_datadisplay
	t_play		p;
	// t_play	c;

	p.mlx = mlx_init();
	p.disp.addr = NULL;
	if (parsing(&p, argv))
		return (ft_puterror(argc, &p));

	// d = get_map(argv);
	//	check_map(d.map);
	// d = save_player_pos(d);
	// d = erase_whitespace(d);
	// d = get_same_size_all_lines(d);
	// c = init_t_play(&d);
	// p = &c;
	p.mouse = 1;
	p.showmap = 0;
	p.win = mlx_new_window(p.mlx, 400, 200, "Cub3d");
	p.disp.img = mlx_new_image(p.mlx, 400, 200);
	p.mmap.img = mlx_new_image(p.mlx, 50, 50);
	p.disp.addr = mlx_get_data_addr(p.disp.img, &p.disp.bits_per_pixel,
			&p.disp.line_length, &p.disp.endian);
	p.mmap.addr = mlx_get_data_addr(p.mmap.img, &p.mmap.bits_per_pixel,
			&p.mmap.line_length, &p.mmap.endian);
	raycast_loop(&p, 400, 200);
	mlx_mouse_move(p.win, 200, 100);
	mlx_hook(p.win, 17, 1L << 2, red_cross, &p);
	mlx_hook(p.win, 2, 1L << 0, readkeys, &p);
	mlx_hook(p.win, 6, 1L << 6, mousing, &p);
	mlx_loop(p.mlx);
	return (0);
}
