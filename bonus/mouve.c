/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:48 by ktroude           #+#    #+#             */
/*   Updated: 2022/06/15 15:27:53 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	readkeys(int keys, t_play *p)
{
	if (keys == 53)
		wclose(p);
	if (keys == 13)
		p->keys.w = 0;
	if (keys == 1)
		p->keys.s = 0;
	if (keys == 124)
		p->keys.left = 0;
	if (keys == 123)
		p->keys.right = 0;
	if (keys == 0)
		p->keys.a = 0;
	if (keys == 2)
		p->keys.d = 0;
	return (0);
}

int	move_up(t_play *p)
{
	mlx_clear_window(p->mlx, p->win);
	if (p->map[(int)(p->posy + p->diry * p->movespeed)][(int)(p->posx)] == '0')
		p->posy += p->diry * p->movespeed;
	if (p->map[(int)(p->posy)][(int)(p->posx + p->dirx * p->movespeed)] == '0')
		p->posx += p->dirx * p->movespeed;
	p->keys.w = 0;
	return (0);
}

int	move_down(t_play *p)
{
	mlx_clear_window(p->mlx, p->win);
	if (p->map[(int)(p->posy - p->diry * p->movespeed)][(int)(p->posx)] == '0')
		p->posy -= p->diry * p->movespeed;
	if (p->map[(int)(p->posy)][(int)(p->posx - p->dirx * p->movespeed)] == '0')
		p->posx -= p->dirx * p->movespeed;
	return (0);
}

int	rotate_left(t_play *p)
{
	mlx_clear_window(p->mlx, p->win);
	p->olddirx = p->dirx;
	p->dirx = p->dirx * cos(-p->rotspeed) - p->diry * sin(-p->rotspeed);
	p->diry = p->olddirx * sin(-p->rotspeed) + p->diry * cos(-p->rotspeed);
	p->oldplanx = p->planex;
	p->planex = p->planex * cos(-p->rotspeed) - p->planey * sin(-p->rotspeed);
	p->planey = p->oldplanx * sin(-p->rotspeed) + p->planey * cos(-p->rotspeed);
	return (0);
}

int	rotate_right(t_play *p)
{
	mlx_clear_window(p->mlx, p->win);
	p->olddirx = p->dirx;
	p->dirx = p->dirx * cos(p->rotspeed) - p->diry * sin(p->rotspeed);
	p->diry = p->olddirx * sin(p->rotspeed) + p->diry * cos(p->rotspeed);
	p->oldplanx = p->planex;
	p->planex = p->planex * cos(p->rotspeed) - p->planey * sin(p->rotspeed);
	p->planey = p->oldplanx * sin(p->rotspeed) + p->planey * cos(p->rotspeed);
	return (0);
}
