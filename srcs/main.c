/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:27:27 by jforner           #+#    #+#             */
/*   Updated: 2022/05/25 18:48:16 by ktroude          ###   ########.fr       */
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
		//	check_map(d.map);
		d = save_player_pos(d);
		d = erase_whitespace(d);
		d = get_same_size_all_lines(d);
		c = init_t_play(&d);
		p = &c;
		p->mlx = mlx_init();
		p->win = mlx_new_window(p->mlx, 400, 200, "Cub3d");
		raycast_loop(p, 400, 200);
		mlx_loop(p->mlx);
	}
}
