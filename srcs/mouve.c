/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:48 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/25 18:44:35 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	readkeys(int keys, t_play *p)
{
	if (keys == 126)
		return (move_up(p));
	if (keys == 125)
		return (move_down(p));
	if (keys == 124)
		return (rotate_left(p));
	if (keys == 123)
		return (rotate_right(p));
	return (0);
}

int	move_up(t_play *p)
{
	mlx_clear_window(p->mlx, p->win);
	if (p->map[(int)(p->posy + p->diry * p->movespeed)][(int)(p->posx)] == '0')
		p->posy += p->diry * p->movespeed;
	if (p->map[(int)(p->posy)][(int)(p->posx + p->dirx * p->movespeed)] == '0')
		p->posx += p->dirx * p->movespeed;
	raycast_loop(p, 400, 200);
	return (0);
}

int	move_down(t_play *p)
{
	mlx_clear_window(p->mlx, p->win);
	if (p->map[(int)(p->posy - p->diry * p->movespeed)][(int)(p->posx)] == '0')
		p->posy -= p->diry * p->movespeed;
	if (p->map[(int)(p->posy)][(int)(p->posx - p->dirx * p->movespeed)] == '0')
		p->posx -= p->dirx * p->movespeed;
	raycast_loop(p, 400, 200);
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
	raycast_loop(p, 400, 200);
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
	raycast_loop(p, 400, 200);
	return (0);
}
