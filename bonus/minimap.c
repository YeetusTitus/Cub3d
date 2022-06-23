/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:22:02 by jforner           #+#    #+#             */
/*   Updated: 2022/06/16 15:22:19 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	mmap_print(t_play *p, int show)
{
	int	i;
	int	j;
	int	xmap;
	int	ymap;
	int	coord[2];

	i = -1;
	xmap = (int)((7 * SCREENWIDTH) / 400);
	ymap = (int)((7 * SCREENHEIGHT) / 200);
	while (++i < (xmap * 7) + 1)
	{
		j = -1;
		while (++j < (ymap * 7) + 1)
		{
			coord[0] = (int)p->posx + (int)((i / xmap) - 3);
			coord[1] = (int)p->posy + (int)((j / ymap) - 3);
			mmap_color(p, i, j, coord);
			p->color = get_data_color(SCREENWIDTH / 20 + i,
					SCREENHEIGHT / 10 + j, p->disp);
			if (show)
				ft_pixel_put(&p->mmap, i, j, p->color);
		}
	}
}

void	mmap_color(t_play *p, int i, int j, int coord[2])
{
	int	xmap;
	int	ymap;

	xmap = (int)((7 * SCREENWIDTH) / 400);
	ymap = (int)((7 * SCREENHEIGHT) / 200);
	if (i % xmap == 0 || j % ymap == 0 || i == xmap * 7 || j == ymap * 7)
		ft_pixel_put(&p->mmap, i, j, 0x00000000);
	else
	{
		if (i / xmap == 3 && j / ymap == 3)
			ft_pixel_put(&p->mmap, i, j, 0x880000FF);
		else if (coord[0] <= 0 || coord[1] <= 0 || coord[0] >= p->lenght
			|| coord[1] >= p->height || p->map[coord[1]][coord[0]] == '1')
			ft_pixel_put(&p->mmap, i, j, 0x88696969);
		else
			ft_pixel_put(&p->mmap, i, j, 0x88FFFFFF);
	}
}

void	create_hide(t_play *p)
{
	int	i;
	int	j;
	int	xmap;
	int	ymap;

	xmap = (int)((7 * SCREENWIDTH) / 400);
	ymap = (int)((7 * SCREENHEIGHT) / 200);
	p->hide.img = mlx_new_image(p->mlx, (((7 * SCREENWIDTH) / 400) * 7) + 1,
			(((7 * SCREENHEIGHT) / 200) * 7) + 1);
	p->hide.addr = mlx_get_data_addr(p->hide.img, &p->hide.bits_per_pixel,
			&p->hide.line_length, &p->hide.endian);
	i = -1;
	while (++i < (xmap * 7) + 1)
	{
		j = -1;
		while (++j < (ymap * 7) + 1)
			ft_pixel_put(&p->mmap, i, j, 0x0);
	}
}
