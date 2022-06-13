/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:40:33 by ktroude           #+#    #+#             */
/*   Updated: 2022/06/06 19:44:28 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_loop(t_play *p, int w, int h)
{
	int	x;
	int	texwidth;
	int	texheight;

	x = 0;
	texwidth = 64;
	texheight = 64;
	p = load_texture(p);
	p = init_t_play(p);
	while (x++ < w)
	{
		p = init_DDA(p, x, w);
		p = step_n_sidedist(p);
		p = perform_DDA(p);
		p = wall_size(p, h);
		p = texture_calcul(p, texwidth, texheight, h);
		p = write_color_in_buffer(p, texheight, texwidth, x);
		p = texture_floor_n_ceil(p, h, x, texheight, texwidth);
	}
	p = display_n_free_buffer(p, h, w);
	mlx_put_image_to_window(p->mlx, p->win, p->disp.img, 0, 0);
	mlx_hook(p->win, 17, 1L << 2, red_cross, &p);
	mlx_hook(p->win, 2, 1L << 0, readkeys, p);
	mlx_hook(p->win, 6, 1L << 6, mousing, p);
	mlx_loop(p->mlx);
}

t_play	*load_texture(t_play *p)
{
	int	sizeh;
	int	sizew;

	sizeh = 64;
	sizew = 64;
	p->text[0].addr = mlx_get_data_addr(p->text[0].img, &p->text[0].bits_per_pixel, &p->text[0].line_length,
								&p->text[0].endian);
	p->text[1].addr = mlx_get_data_addr(p->text[1].img, &p->text[1].bits_per_pixel, &p->text[1].line_length,
								&p->text[0].endian);
	p->text[2].addr = mlx_get_data_addr(p->text[2].img, &p->text[2].bits_per_pixel, &p->text[2].line_length,
								&p->text[2].endian);
	p->text[3].addr = mlx_get_data_addr(p->text[3].img, &p->text[3].bits_per_pixel, &p->text[3].line_length,
								&p->text[3].endian);
	p->text[4].img = mlx_xpm_file_to_image(p->mlx, "./content/greystone.xpm", &sizew, &sizeh);
	p->text[4].addr = mlx_get_data_addr(p->text[4].img, &p->text[4].bits_per_pixel, &p->text[4].line_length,
								&p->text[4].endian);
	p->text[5].img = mlx_xpm_file_to_image(p->mlx, "./content/wood.xpm", &sizew, &sizeh);
	p->text[5].addr = mlx_get_data_addr(p->text[5].img, &p->text[5].bits_per_pixel, &p->text[5].line_length,
								&p->text[5].endian);
	return (p);
}

t_play	*init_t_play(t_play *p)
{
	p->movespeed = 0.2;
	p->rotspeed = 0.1;
	return (p);
}

t_play	*init_DDA(t_play *p, int x, int w)
{
	p->camerax = 2 * x / (double)w - 1;
	p->raydirx = p->dirx + p->planex * p->camerax;
	p->raydiry = p->diry + p->planey * p->camerax;
	p->mapx = (int)p->posx;
	p->mapy = (int)p->posy;
	if (p->raydirx == 0)
			p->deltadistx = 1e30;
	else
		p->deltadistx = fabs(1 / p->raydirx);
	if (p->raydiry == 0)
		p->deltadisty = 1e30;
	else
		p->deltadisty = fabs(1 / p->raydiry);
	p->hit = 0;
	return (p);
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

t_play	*perform_DDA(t_play *p)
{
	while (p->hit == 0)
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
		if (p->map[p->mapx][p->mapy] != '0') 
			p->hit = 1;
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

t_play	*texture_calcul(t_play *p, int texwidth, int texheight, int h)
{
	if (p->side == 0)
		p->wallx = p->posy + p->perpwalldist * p->raydiry;
    else
		p->wallx = p->posx + p->perpwalldist * p->raydirx;
    p->wallx -= floor((p->wallx));
	p->texx = (int)(p->wallx * (double)(texwidth));
    if (p->side == 0 && p->raydirx > 0)
		p->texx = texwidth - p->texx - 1;
    if (p->side == 1 && p->raydiry < 0)
		p->texx = texwidth - p->texx - 1;
	p->step = 1.0 * texheight / p->lineheight;
	p->texpos = (p->drawstart - h / 2 + p->lineheight / 2) * p->step;
	return (p);
}

t_play	*write_color_in_buffer(t_play *p, int texheight, int texwidth, int x)
{
	int		y;
	char	*dst;

	y = 0;
	while (y++ < p->drawstart)
		p->buffer[y][x] = 4534;
	while (y++ < p->drawend)
	{
		p->texy = (int)p->texpos & (texheight - 1);
        p->texpos += p->step;
		if (p->side > 0 && p->stepy > 0) // face sud
			p->color = get_data_color(p->texx, p->texy, 0, p);
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
		p->buffer[y][x] = p->color;
	}
	while (y++ < 200)
		p->buffer[y][x] = 121;
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

t_play  *texture_floor_n_ceil(t_play *p, int h, int x, int texheight, int texwidth)
{
    int     y;

    y = p->drawend - 1;
    if(p->side == 0 && p->raydirx > 0)
    {
        p->floorxwall = p->mapx;
        p->floorywall = p->mapy + p->wallx;
    }
    else if(p->side == 0 && p->raydirx < 0)
    {
        p->floorxwall = p->mapx + 1.0;
        p->floorywall = p->mapy + p->wallx;
    }
    else if(p->side == 1 && p->raydiry > 0)
    {
        p->floorxwall = p->mapx + p->wallx;
        p->floorywall = p->mapy;
    }
    else
    {
        p->floorxwall = p->mapx + p->wallx;
        p->floorywall = p->mapy + 1.0;
    }
    p->distwall = p->perpwalldist;
    p->distplayer = 0.0;
    if (p->drawend < 0)
        p->drawend = h;
          while (y++ < h)
    {
        p->currentdist = h / (2.0 * y - h);
        p->weight = (p->currentdist - p->distplayer) / (p->distwall - p->distplayer);
        p->currentfloorx = p->weight * p->floorxwall + (1.0 - p->weight) * p->posx;
        p->currentfloory = p->weight * p->floorywall + (1.0 - p->weight) * p->posy;
        p->floortexx = (int)(p->currentfloorx * texwidth) % texwidth;
        p->floortexy = (int)(p->currentfloory * texheight) % texheight;
        //floor
        p->color = get_data_color(p->floortexx, p->floortexy, 4, p);
        p->buffer[y][x] = p->color;
        //ceiling (symmetrical!)
        p->color = get_data_color(p->floortexx, p->floortexy, 5, p);
        p->buffer[h - y][x] = p->color;
    }
    return (p);
}

