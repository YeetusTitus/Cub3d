/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:22:02 by jforner           #+#    #+#             */
/*   Updated: 2022/06/15 14:30:04 by jforner          ###   ########.fr       */
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
			if (show)
				ft_pixel_put(&p->mmap, i, j,
					(get_data_color(SCREENWIDTH / 20 + i,
							SCREENHEIGHT / 10 + j, p->disp)));
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

int	get_data_color(int x, int y, t_disp disp)
{
	char	*dst;

	dst = disp.addr + (y * disp.line_length + x * (disp.bits_per_pixel / 8));
	return (*(int *)dst);
}
