/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:40:33 by ktroude           #+#    #+#             */
/*   Updated: 2022/05/25 18:51:20 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_play	init_t_play(t_data *d)
{
	t_play	p;

	p.posx = d->pos[1];
	p.posy = d->pos[0];
	p = get_dir_x_y(d->orientation, p);
	p.dirx = -1;
	p.diry = 0;
	p.planex = 0;
	p.planey = 0.66;
	p.map = d->map;
	return (p);
}

t_play	get_dir_x_y(char c, t_play p)
{
	if (c == 'N')
	{
		p.dirx = 0;
		p.diry = 1;
	}
	if (c == 'S')
	{
		p.dirx = 0;
		p.diry = -1;
	}
	if (c == 'E')
	{
		p.dirx = 1;
		p.diry = 0;
	}
	if (c == 'W')
	{
		p.dirx = -1;
		p.diry = 0;
	}
	return (p);
}

void	verline(int x, t_play *p)
{
	while (p->drawstart < p->drawend)
		mlx_pixel_put(p->mlx, p->win, x, p->drawstart++, p->color);
}

void	raycast_loop(t_play *p, int w, int h)
{
	int	x;

	x = 0;
	while (x++ < w)
	{
		p->camerax = 2 * x / (double)(w) - 1;
		p->raydirx = p->dirx + p->planex * p->camerax;
		p->raydiry = p->diry + p->planey * p->camerax;
		p->mapx = (int)(p->posx);
		p->mapy = (int)(p->posy);
		p->deltadistx = (p->raydirx == 0) ? 1e30 : fabs(1 / p->raydirx);
		p->deltadisty = (p->raydiry == 0) ? 1e30 : fabs(1 / p->raydiry);
		p->hit = 0;
		p = get_step_n_sidedist_incr(p);
		while (p->hit == 0)
			p = get_hit(p, h);
		if (p->side > 0 && p->stepy > 0) // face sud
			p->color = 0x00FF0000;
		if (p->side > 0 && p->stepy <= 0) // face nord
			p->color = 0x00FF0000 / 2;
		if (p->side == 0 && p->stepx > 0) // face ouest
			p->color = 0x00FF0000 / 4;
		if (p->side == 0 && p->stepx <= 0) // est
			p->color = 0x00FF0000 / 6;

		verline(x, p);
	}
	p->movespeed = 0.2;
	p->rotspeed = 0.1;
	mlx_hook(p->win, 2, 1L << 0, readkeys, p);
	mlx_loop(p->mlx);
}

t_play	*get_step_n_sidedist_incr(t_play *p)
{
	if (p->raydirx < 0)
	{
		p->stepx = -1;
		p->sidedistx = (p->posx - p->mapx) * p->deltadistx;
	}
	else
	{
		p->stepx = 1;
		p->sidedistx = (p->mapx + 1.0 - p->posx) * p->deltadistx;
	}
	if (p->raydiry < 0)
	{
		p->stepy = -1;
		p->sidedisty = (p->posy - p->mapy) * p->deltadisty;
	}
	else
	{
		p->stepy = 1;
		p->sidedisty = (p->mapy + 1.0 - p->posy) * p->deltadisty;
	}
	return (p);
}

t_play	*get_hit(t_play *p, int h)
{
	if (p->sidedistx < p->sidedisty)
	{
		p->sidedistx += p->deltadistx;
		p->mapx += p->stepx;
		p->side = 0;
	}
	else
	{
		p->sidedisty += p->deltadisty;
		p->mapy += p->stepy;
		p->side = 1;
	}
	if (p->map[p->mapy][p->mapx] != '0')
		p->hit = 1;
	if (p->side == 0)
		p->perpwalldist = (p->sidedistx - p->deltadistx);
	else
		p->perpwalldist = (p->sidedisty - p->deltadisty);
	p->lineheight = (int)(h / p->perpwalldist);
	p->drawstart = -p->lineheight / 2 + h / 2;
	if (p->drawstart < 0)
		p->drawstart = 0;
	p->drawend = p->lineheight / 2 + h / 2;
	if (p->drawend >= h)
		p->drawend = h - 1;
	return (p);
}



/*
t_play	*get_texture(t_play *p, int h, int w)
{
	int	**tab;
	int	i;
	int	***arr;

	i = 0;
	tab = malloc(sizeof(int *) * h);
	while (i++ < h)
		tab[i] = malloc(sizeof(int) * w);
	i = 0;
	arr = malloc(sizeof(int **) * 4); // nb de texture a modifier ici;
	while (i++ < 4)
		arr[i] = malloc(sizeof(tab));
	i = 0;
	while (i < h)
		free(tab[i++]);
	free(tab);
	p->texture = arr;
	return (p);
}

t_play	*generate_texture(t_play *p)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x++ < )

}

*/