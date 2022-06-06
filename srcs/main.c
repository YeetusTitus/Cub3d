/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:27:27 by jforner           #+#    #+#             */
/*   Updated: 2022/06/06 18:36:08 by jforner          ###   ########.fr       */
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
	p.xmouse = -342;
	p.win = mlx_new_window(p.mlx, 400, 200, "Cub3d");
	p.disp.img = mlx_new_image(p.mlx, 400, 200);
	p.disp.addr = mlx_get_data_addr(p.disp.img, &p.disp.bits_per_pixel,
			&p.disp.line_length, &p.disp.endian);
	raycast_loop(&p, 400, 200);
	mlx_loop(p.mlx);
	return (0);
}
