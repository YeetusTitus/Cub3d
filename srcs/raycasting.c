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
	p->text[0].img = mlx_xpm_file_to_image(p->mlx, "./content/colorstone.xpm", &sizew, &sizeh);
	p->text[0].addr = mlx_get_data_addr(p->text[0].img, &p->text[0].bits_per_pixel, &p->text[0].line_length,
								&p->text[0].endian);
	p->text[1].img = mlx_xpm_file_to_image(p->mlx, "./content/greystone.xpm", &sizew, &sizeh);
	p->text[1].addr = mlx_get_data_addr(p->text[1].img, &p->text[1].bits_per_pixel, &p->text[1].line_length,
								&p->text[0].endian);
	p->text[2].img = mlx_xpm_file_to_image(p->mlx, "./content/bluestone.xpm", &sizew, &sizeh);
	p->text[2].addr = mlx_get_data_addr(p->text[2].img, &p->text[2].bits_per_pixel, &p->text[2].line_length,
								&p->text[2].endian);
	p->text[3].img = mlx_xpm_file_to_image(p->mlx, "./content/redbrick.xpm", &sizew, &sizeh);
	p->text[3].addr = mlx_get_data_addr(p->text[3].img, &p->text[3].bits_per_pixel, &p->text[3].line_length,
								&p->text[3].endian);
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
	if (p->lineheight > h)
		p->lineheight = h;
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

	printf("line == %d\n", p->lineheight);
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






/*
void	verline(int x, t_play *p)
{
	int	i;

	i = -1;
	while (++i < p->drawstart)
		ft_pixel_put(&p->disp, x, i, p->texture->ceil);
	while (p->drawstart < p->drawend)
		ft_pixel_put(&p->disp, x, p->drawstart++, p->color);
	i = p->drawend;
	while (i < 200 && p->drawend < 200 - 2)
		ft_pixel_put(&p->disp, x, i++, p->texture->floor);
}

void	raycast_loop(t_play *p, int w, int h)
{

int	sizew = 64;
int	sizeh = 64;
char *dst;
int	x = 0;
int	y = 0;
// int	start = 0;
h = 200;
p->text[0].img = mlx_xpm_file_to_image(p->mlx, "./content/colorstone.xpm", &sizew, &sizeh);
	p->text[0].addr = mlx_get_data_addr(p->text[0].img, &p->text[0].bits_per_pixel, &p->text[0].line_length,
								&p->text[0].endian);
p->text[1].img = mlx_xpm_file_to_image(p->mlx, "./content/greystone.xpm", &sizew, &sizeh);
	p->text[1].addr = mlx_get_data_addr(p->text[1].img, &p->text[1].bits_per_pixel, &p->text[1].line_length,
								&p->text[0].endian);
p->text[2].img = mlx_xpm_file_to_image(p->mlx, "./content/bluestone.xpm", &sizew, &sizeh);
	p->text[2].addr = mlx_get_data_addr(p->text[2].img, &p->text[2].bits_per_pixel, &p->text[2].line_length,
								&p->text[2].endian);
p->text[3].img = mlx_xpm_file_to_image(p->mlx, "./content/redbrick.xpm", &sizew, &sizeh);
	p->text[3].addr = mlx_get_data_addr(p->text[3].img, &p->text[3].bits_per_pixel, &p->text[3].line_length,
								&p->text[3].endian);

	for(int x = 0; x < 64; x++)
		for(int y = 0; y < 64; y++)
		{
			p->text[0].tab[64 * y + x] = get_data_color(x, y, 0, p);
			p->text[1].tab[64 * y + x] = get_data_color(x, y, 1, p);
			p->text[2].tab[64 * y + x] = get_data_color(x, y, 2, p);
			p->text[3].tab[64 * y + x] = get_data_color(x, y, 3, p);
		}

	x = -1;
	y = -1;

	while (++x < 400)
	{
		p->camerax = 2 * x / (double)(w) - 1.0;
		p->raydirx = p->dirx + p->planex * p->camerax;
		p->raydiry = p->diry + p->planey * p->camerax;
		p->mapx = (int)(p->posx);
		p->mapy = (int)(p->posy);
		if (p->raydirx == 0)
			p->deltadistx = 1e30;
		else
			p->deltadistx = fabs(1.0 / p->raydirx);
		if (p->raydiry == 0)
			p->deltadisty = 1e30;
		else
			p->deltadisty = fabs(1.0 / p->raydiry);
		p->hit = 0;
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
			if (p->map[p->mapy][p->mapx] != '0')
				p->hit = 1;
		}
		if (p->side == 0)
			p->perpwalldist = (p->sidedistx - p->deltadistx);
		else
			p->perpwalldist = (p->sidedisty - p->deltadisty);
		p->lineheight = (int)(200 / p->perpwalldist);
		p->drawstart = -p->lineheight / 2 + 200 / 2;
		if (p->drawstart < 0)
			p->drawstart = 0;
		p->drawend = p->lineheight / 2 + 200 / 2;
		if (p->drawend >= 200)
			p->drawend = 200 - 1;

/////////////////////////////////

		if (p->side == 0)
			p->wallx = p->posy + p->perpwalldist * p->raydiry;
		else
			p->wallx = p->posx + p->perpwalldist * p->raydirx;
		p->wallx -= floor(p->wallx);


		p->texx = (int)p->wallx * 64;
		if (p->side == 0 && p->raydirx > 0)
			p->texx = 64 - p->texx; //- 1;
		if (p->side == 1 && p->raydiry < 0)
			p->texx = 64 - p->texx; // - 1;

		if (p->lineheight > 200)
		{			
			p->lineheight = 200;
		}
		p->drawstart = -p->lineheight / 2 + 200 / 2; 
		p->step = 64.0 / p->lineheight;
		p->texpos = (p->drawstart - 200 / 2 + p->lineheight / 2) * p->step;
		// printf("dist == %f\n", p->perpwalldist);
		// printf("drawS = %d\n", p->drawstart);
		// printf("lineH = %d\n", p->lineheight);
		// printf("texpos == %f\n", p->texpos);
		// printf("step == %f\n", p->step);
		int	y = p->drawstart; // -1 really?
		while (y++ < p->drawend)
		{
			p->texy = (int)p->texpos & (64 - 1);
			p->texpos += p->step;
			if (p->side > 0 && p->stepy > 0) // face sud
			{
				dst = p->text[0].addr + ((int)(p->texy) % sizeh
				* p->text[0].line_length + p->texx % sizew
				* (p->text[0].bits_per_pixel / 8));
				p->color = *(unsigned int *)dst;
			}
			if (p->side > 0 && p->stepy <= 0) // face nord
				p->color =  get_data_color(x, p->texy, 1, p);
			if (p->side == 0 && p->stepx > 0) // face ouest
				p->color =  get_data_color(x, p->texy, 2, p);
			if (p->side == 0 && p->stepx <= 0) // est
				p->color =  get_data_color(x, p->texy, 3, p);
			p->buffer[y][x] = p->color;
		}
	}
	x = 0;
	y = 0;
		while (y < 200)
		{
			while (x < 400)
			{
			ft_pixel_put(&p->disp, x, y, p->buffer[y][x]);
				p->buffer[y][x] = 0;
				x++;
			}
			y++;
			x = 0;
		}
	mlx_put_image_to_window(p->mlx, p->win, p->disp.img, 0, 0);
	p->movespeed = 0.2;
	p->rotspeed = 0.1;
	mlx_hook(p->win, 17, 1L << 2, red_cross, &p);
	mlx_hook(p->win, 2, 1L << 0, readkeys, p);
	mlx_hook(p->win, 6, 1L << 6, mousing, p);
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

t_play	*get_hit(t_play *p)
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
	return (p);
}
*/