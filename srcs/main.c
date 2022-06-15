/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:27:27 by jforner           #+#    #+#             */
/*   Updated: 2022/06/15 14:33:14 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_play	p;

	p.mlx = mlx_init();
	p.disp.addr = NULL;
	if (parsing(&p, argv))
		return (ft_puterror(argc, &p));
	p.mouse = 1;
	p.keys.w = 1;
	p.keys.s = 1;
	p.keys.a = 1;
	p.keys.d = 1;
	p.keys.right = 1;
	p.keys.left = 1;
	p.showmap = 0;
	p.xmouse = (SCREENWIDTH / 2);
	p.win = mlx_new_window(p.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	p.disp.img = mlx_new_image(p.mlx, SCREENWIDTH, SCREENHEIGHT);
	p.mmap.img = mlx_new_image(p.mlx, (((7 * SCREENWIDTH) / 400) * 7) + 1,
			(((7 * SCREENHEIGHT) / 200) * 7) + 1);
	p.disp.addr = mlx_get_data_addr(p.disp.img, &p.disp.bits_per_pixel,
			&p.disp.line_length, &p.disp.endian);
	p.mmap.addr = mlx_get_data_addr(p.mmap.img, &p.mmap.bits_per_pixel,
			&p.mmap.line_length, &p.mmap.endian);
	load_texture(&p);
	raycast_loop(&p, SCREENWIDTH, SCREENHEIGHT);
	mlx_mouse_move(p.win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mlx_hook(p.win, 17, 1L << 2, red_cross, &p);
	mlx_hook(p.win, 2, 1L << 0, readkeys, &p);
	mlx_key_hook(p.win, readkeys2, &p);
	mlx_hook(p.win, 6, 1L << 6, mousing, &p);
	mlx_loop_hook(p.mlx, display_loop, &p);
	mlx_loop(p.mlx);
	return (0);
}
