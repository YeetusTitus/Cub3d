/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:40:33 by ktroude           #+#    #+#             */
/*   Updated: 2022/06/13 14:01:51 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verline(int x, t_play *p)
{
	int	i;

	i = -1;
	while (++i < p->drawstart)
		ft_pixel_put(&p->disp, x, i, p->texture->ceil);
	while (p->drawstart < p->drawend)
		ft_pixel_put(&p->disp, x, p->drawstart++, p->color);
	i = p->drawend;
	while (i < 200 && p->drawend < 198)
		ft_pixel_put(&p->disp, x, i++, p->texture->floor);
}

void	raycast_loop(t_play *p, int w, int h)
{
	int	x;

	x = -1;
	while (++x < w)
	{
		p->camerax = 2 * x / (double)(w) - 1;
		p->raydirx = p->dirx + p->planex * p->camerax;
		p->raydiry = p->diry + p->planey * p->camerax;
		p->mapx = (int)(p->posx);
		p->mapy = (int)(p->posy);
		if (p->raydirx == 0)
			p->deltadistx = 1;
		else
			p->deltadistx = fabs(1 / p->raydirx);
		if (p->raydiry == 0)
			p->deltadisty = 1;
		else
			p->deltadisty = fabs(1 / p->raydiry);
		p->hit = 0;
		p = get_step_n_sidedist_incr(p);
		// printf("Well cum !\n");
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
	mlx_put_image_to_window(p->mlx, p->win, p->disp.img, 0, 0);
	if (!(p->showmap))
	{
		mmap_print(p, 0);
		mlx_put_image_to_window(p->mlx, p->win, p->mmap.img, 20, 20);
	}
	p->movespeed = 0.2;
	p->rotspeed = 0.1;
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
	// printf("y = %d\tx = %d\n", p->mapy, p->mapx);
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
	// printf("y = %d\tx = %d\n", p->mapy, p->mapx);mak
	if (p->map[p->mapy][p->mapx] != '0')
		p->hit = 1;
		// printf("pull down !\n");
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