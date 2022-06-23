/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:17:32 by jforner           #+#    #+#             */
/*   Updated: 2022/06/16 15:12:44 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	show_mouse(t_play *play)
{
	if (play->mouse)
	{
		mlx_mouse_hide();
		play->mouse = 0;
	}
	else
	{
		mlx_mouse_show();
		play->mouse = 1;
	}
	return (0);
}

int	show_mmmap(t_play *p)
{
	if (p->showmap)
		p->showmap = 0;
	else
		p->showmap = 1;
	mmap_print(p, p->showmap);
	if (p->showmap)
		mlx_put_image_to_window(p->mlx, p->win, p->hide.img,
			SCREENWIDTH / 20, SCREENHEIGHT / 10);
	mlx_put_image_to_window(p->mlx, p->win, p->mmap.img,
		SCREENWIDTH / 20, SCREENHEIGHT / 10);
	return (0);
}

int	readkeys2(int key, t_play *p)
{
	if (key == 257)
		show_mouse(p);
	if (key == 46)
		show_mmmap(p);
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
	if (!p->keys.left || p->xmouse > (SCREENWIDTH / 2))
		rotate_left(p);
	if (!p->keys.right || p->xmouse < (SCREENWIDTH / 2))
		rotate_right(p);
	if (!display)
	{
		p->rotspeed = 0.025;
		p->xmouse = (SCREENWIDTH / 2);
		raycast_loop(p, SCREENWIDTH, SCREENHEIGHT);
	}
	return (0);
}
