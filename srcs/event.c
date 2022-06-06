/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:18:59 by jforner           #+#    #+#             */
/*   Updated: 2022/06/03 23:14:11 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	red_cross(int keycode, int x, int y, t_play *play)
{
	(void)keycode;
	(void)x;
	(void)y;
	(void)(play);
	exit(EXIT_SUCCESS);
}

int	wclose(t_play *play)
{
	mlx_destroy_window(play->mlx, play->win);
	freedom(play);
	exit(EXIT_SUCCESS);
	return (1);
}

int	move_left(t_play *p)
{
	double	direx;
	double	direy;

	direx = p->dirx * cos(M_PI_2) - p->diry * sin(M_PI_2);
	direy = p->dirx * sin(M_PI_2) + p->diry * cos(M_PI_2);
	printf("dir x = %f  | dir y = %f\n", direx, direy);
	mlx_clear_window(p->mlx, p->win);
	if (p->map[(int)(p->posy + direy * p->movespeed)][(int)(p->posx)] == '0')
		p->posy += direy * p->movespeed;
	if (p->map[(int)(p->posy)][(int)(p->posx + direx * p->movespeed)] == '0')
		p->posx += direx * p->movespeed;
	raycast_loop(p, 400, 200);
	return (0);
}

int	move_right(t_play *p)
{
	double	direx;
	double	direy;

	direx = p->dirx * cos(M_PI_2) - p->diry * sin(M_PI_2);
	direy = p->dirx * sin(M_PI_2) + p->diry * cos(M_PI_2);
	printf("dir x = %f  | dir y = %f\n", direx, direy);
	mlx_clear_window(p->mlx, p->win);
	if (p->map[(int)(p->posy - direy * p->movespeed)][(int)(p->posx)] == '0')
		p->posy -= direy * p->movespeed;
	if (p->map[(int)(p->posy)][(int)(p->posx - direx * p->movespeed)] == '0')
		p->posx -= direx * p->movespeed;
	raycast_loop(p, 400, 200);
	return (0);
}

int	mousing(int x, int y, t_play *play)
{
	static int	min = 0;
	static int	max = 0;

	(void)(y);
	if ((play->xmouse != -342 && x < play->xmouse)
		|| (play->xmouse <= min && x == play->xmouse))
	{
		if (min < x)
			min = x;
		play->xmouse = x;
		rotate_right(play);
	}
	else if ((play->xmouse != -342 && x > play->xmouse)
		|| (play->xmouse >= max && x == play->xmouse))
	{
		if (max < x)
			max = x;
		play->xmouse = x;
		rotate_left(play);
	}
	play->xmouse = x;
	return (0);
}
