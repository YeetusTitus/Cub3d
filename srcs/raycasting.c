/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:40:33 by ktroude           #+#    #+#             */
/*   Updated: 2022/06/16 16:09:38 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	raycast_loop(t_play *p, int w, int h)
{
	int	x;

	x = -1;
	while (++x < w)
	{
		init_dda(p, x, w);
		step_n_sidedist(p);
		perform_dda(p);
		wall_size(p, h);
		texture_calcul(p, h);
		write_color_in_buffer(p, x, h);
		texture_floor_n_ceil(p, h, x);
	}
	display_n_free_buffer(p, h, w);
	mlx_put_image_to_window(p->mlx, p->win, p->disp.img, 0, 0);
	mmap_print(p, p->showmap);
	if (!(p->showmap))
		mlx_put_image_to_window(p->mlx, p->win, p->mmap.img,
			SCREENWIDTH / 20, SCREENHEIGHT / 10);
}

void	step_n_sidedist(t_play *p)
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
}

void	wall_size(t_play *p, int h)
{
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
}

void	write_color_in_buffer(t_play *p, int x, int h)
{
	int		y;

	y = 0;
	while (y < p->drawstart)
		p->buffer[y++][x] = p->texture->ceil;
	while (y < p->drawend + 1)
	{
		p->texy = (int)p->texpos & (TEXHEIGHT - 1);
		p->texpos += p->step;
		if (p->side > 0 && p->stepy > 0)
			p->color = get_data_color(p->texx, p->texy, p->text[0]);
		if (p->side > 0 && p->stepy <= 0)
			p->color = get_data_color(p->texx, p->texy, p->text[1]);
		if (p->side == 0 && p->stepx > 0)
			p->color = get_data_color(p->texx, p->texy, p->text[2]);
		if (p->side == 0 && p->stepx <= 0)
			p->color = get_data_color(p->texx, p->texy, p->text[3]);
		p->buffer[y++][x] = p->color;
	}
	while (y < h)
		p->buffer[y++][x] = p->texture->floor;
}

void	display_n_free_buffer(t_play *p, int h, int w)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < h)
	{
		while (x < w)
		{
			ft_pixel_put(&p->disp, x, y, p->buffer[y][x]);
			p->buffer[y][x] = 0;
			x++;
		}
		x = 0;
		y++;
	}
}
