/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:22:02 by jforner           #+#    #+#             */
/*   Updated: 2022/06/13 16:38:11 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	mmap_print(t_play *p, int show)
{
	int	i;
	int	j;
	int	coord[2];

	i = -1;
	while (++i < 50)
	{
		j = -1;
		while (++j < 50)
		{
			coord[0] = (int)p->posx + ((i / 7) - 3);
			coord[1] = (int)p->posy + ((j / 7) - 3);
			mmap_color(p, i, j, coord);
			if (show)
				ft_pixel_put(&p->mmap, i, j,
					(get_data_color(20 + i, 20 + j, p->disp)));
		}
	}
}

void	mmap_color(t_play *p, int i, int j, int coord[2])
{
	if (i % 7 == 0 || j % 7 == 0 || i == 49 || j == 49)
		ft_pixel_put(&p->mmap, i, j, 0x00000000);
	else
	{
		if (i / 7 == 3 && j / 7 == 3)
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