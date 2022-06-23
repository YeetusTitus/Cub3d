/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texndda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:55:49 by jforner           #+#    #+#             */
/*   Updated: 2022/06/21 11:12:47 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	load_texture(t_play *p)
{
	int	sizeh;
	int	sizew;

	p->text[0].addr = mlx_get_data_addr(p->text[0].img,
			&p->text[0].bits_per_pixel, &p->text[0].line_length,
			&p->text[0].endian);
	p->text[1].addr = mlx_get_data_addr(p->text[1].img,
			&p->text[1].bits_per_pixel, &p->text[1].line_length,
			&p->text[0].endian);
	p->text[2].addr = mlx_get_data_addr(p->text[2].img,
			&p->text[2].bits_per_pixel, &p->text[2].line_length,
			&p->text[2].endian);
	p->text[3].addr = mlx_get_data_addr(p->text[3].img,
			&p->text[3].bits_per_pixel, &p->text[3].line_length,
			&p->text[3].endian);
	p->text[4].img = mlx_xpm_file_to_image(p->mlx,
			"./content/greystone.xpm", &sizew, &sizeh);
	p->text[4].addr = mlx_get_data_addr(p->text[4].img,
			&p->text[4].bits_per_pixel, &p->text[4].line_length,
			&p->text[4].endian);
	p->text[5].img = mlx_xpm_file_to_image(p->mlx,
			"./content/wood.xpm", &sizew, &sizeh);
	p->text[5].addr = mlx_get_data_addr(p->text[5].img,
			&p->text[5].bits_per_pixel, &p->text[5].line_length,
			&p->text[5].endian);
}

void	init_dda(t_play *p, int x, int w)
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
}

void	perform_dda(t_play *p)
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
		if (p->map[p->mapy][p->mapx] != '0')
			p->hit = 1;
	}
}

void	texture_calcul(t_play *p, int h)
{
	if (p->side == 0)
		p->wallx = p->posy + p->perpwalldist * p->raydiry;
	else
		p->wallx = p->posx + p->perpwalldist * p->raydirx;
	p->wallx -= floor((p->wallx));
	p->texx = (int)(p->wallx * (double)(TEXWIDTH));
	if (p->side == 0 && p->raydirx > 0)
		p->texx = TEXWIDTH - p->texx - 1;
	if (p->side == 1 && p->raydiry < 0)
		p->texx = TEXWIDTH - p->texx - 1;
	p->step = (double)TEXHEIGHT / p->lineheight;
	p->texpos = (p->drawstart - h / 2 + p->lineheight / 2) * p->step;
}
