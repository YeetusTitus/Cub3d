/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:40:33 by ktroude           #+#    #+#             */
/*   Updated: 2022/06/15 14:41:05 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	raycast_loop(t_play *p, int w, int h)
{
	int	x;
	int	texwidth;
	int	texheight;

	x = -1;
	texwidth = 64;
	texheight = 64;
	while (++x < w)
	{
		p = init_dda(p, x, w);
		p = step_n_sidedist(p);
		p = perform_dda(p);
		p = wall_size(p, h);
		p = texture_calcul(p, texwidth, texheight, h);
		p = write_color_in_buffer(p, texheight, texwidth, x, h);
		// p = texture_floor_n_ceil(p, h, x, texheight, texwidth);
	}
	p = display_n_free_buffer(p, h, w);
	mlx_put_image_to_window(p->mlx, p->win, p->disp.img, 0, 0);
	mmap_print(p, p->showmap);
	if (!(p->showmap))
		mlx_put_image_to_window(p->mlx, p->win, p->mmap.img,
			SCREENWIDTH / 20, SCREENHEIGHT / 10);
}

t_play	*step_n_sidedist(t_play *p)
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

t_play	*wall_size(t_play *p, int h)
{
	if (p->side == 0)
		p->perpwalldist = (p->sidedistx - p->deltadistx);
    else
		p->perpwalldist = (p->sidedisty - p->deltadisty);
	p->lineheight = (int)(h / p->perpwalldist);
//	if (p->lineheight > h)
//		p->lineheight = h;
	p->drawstart = -p->lineheight / 2 + h / 2;
    if (p->drawstart < 0)
		p->drawstart = 0;
    p->drawend = p->lineheight / 2 + h / 2;
    if (p->drawend >= h)
		p->drawend = h - 1;
	return (p);
}

t_play	*write_color_in_buffer(t_play *p, int texheight, int texwidth, int x, int h)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < p->drawstart)
		p->buffer[y++][x] = p->texture->ceil;
	while (y < p->drawend)
	{
		p->texy = (int)p->texpos & (texheight - 1);
		p->texpos += p->step;
		if (p->side > 0 && p->stepy > 0) // face sud
			p->color = get_data_color(p->texx, p->texy, p->text[0]);
		if (p->side > 0 && p->stepy <= 0) // face nord
		{
			dst = p->text[1].addr + ((int)(p->texy) % texheight
					* p->text[1].line_length + p->texx % texwidth
					* (p->text[1].bits_per_pixel / 8));
			p->color = *(unsigned int *)dst;
		}
		if (p->side == 0 && p->stepx > 0) // face ouest
		{
			dst = p->text[2].addr + ((int)(p->texy) % texheight
					* p->text[2].line_length + p->texx % texwidth
					* (p->text[2].bits_per_pixel / 8));
			p->color = *(unsigned int *)dst;
		}
		if (p->side == 0 && p->stepx <= 0) // est
		{
			dst = p->text[3].addr + ((int)(p->texy) % texheight
					* p->text[3].line_length + p->texx % texwidth
					* (p->text[3].bits_per_pixel / 8));
			p->color = *(unsigned int *)dst;
		}
		p->buffer[y++][x] = p->color;
	}
	while (y < h)
		p->buffer[y++][x] = p->texture->floor;
	return (p);
}

t_play	*display_n_free_buffer(t_play *p, int h, int w)
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
	return (p);
}
