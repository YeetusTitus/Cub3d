/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:27:27 by jforner           #+#    #+#             */
/*   Updated: 2022/06/21 11:44:37 by jforner          ###   ########.fr       */
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
	init_win(&p);
	create_hide(&p);
	load_texture(&p);
	raycast_loop(&p, SCREENWIDTH, SCREENHEIGHT);
	mlx_hook(p.win, 17, 1L << 2, red_cross, &p);
	mlx_hook(p.win, 2, 1L << 0, readkeys, &p);
	mlx_key_hook(p.win, readkeys2, &p);
	mlx_loop_hook(p.mlx, display_loop, &p);
	mlx_loop(p.mlx);
	return (0);
}
