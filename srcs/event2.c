/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:17:32 by jforner           #+#    #+#             */
/*   Updated: 2022/06/21 11:44:08 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	readkeys2(int key, t_play *p)
{
	if (key == 13)
		p->keys.w = 1;
	if (key == 1)
		p->keys.s = 1;
	if (key == 124)
		p->keys.left = 1;
	if (key == 123)
		p->keys.right = 1;
	if (key == 0)
		p->keys.a = 1;
	if (key == 2)
		p->keys.d = 1;
	return (0);
}

int	display_loop(t_play *p)
{
	int	display;

	display = 1;
	if (!p->keys.a || !p->keys.s || !p->keys.left || !p->keys.right
		|| !p->keys.d || !p->keys.w || p->xmouse != (SCREENWIDTH / 2))
		display = 0;
	if (!p->keys.a)
		move_left(p);
	if (!p->keys.d)
		move_right(p);
	if (!p->keys.w)
		move_up(p);
	if (!p->keys.s)
		move_down(p);
	if (!p->keys.left)
		rotate_left(p);
	if (!p->keys.right)
		rotate_right(p);
	if (!display)
	{
		p->rotspeed = 0.025;
		raycast_loop(p, SCREENWIDTH, SCREENHEIGHT);
	}
	return (0);
}
