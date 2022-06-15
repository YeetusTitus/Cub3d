/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:17:32 by jforner           #+#    #+#             */
/*   Updated: 2022/06/15 13:01:03 by jforner          ###   ########.fr       */
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

int	show_mmmap(t_play *play)
{
	if (play->showmap)
		play->showmap = 0;
	else
		play->showmap = 1;
	mmap_print(play, play->showmap);
	mlx_put_image_to_window(play->mlx, play->win, play->mmap.img,
		SCREENWIDTH / 20, SCREENHEIGHT / 10);
	return (0);
}

void	ft_pixel_put(t_disp *display, int x, int y, int color)
{
	char	*dst;

	dst = display->addr
		+ (y * display->line_length + x * (display->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
		p->xmouse = (SCREENWIDTH / 2);
		raycast_loop(p, SCREENWIDTH, SCREENHEIGHT);
	}
	return (0);
}
