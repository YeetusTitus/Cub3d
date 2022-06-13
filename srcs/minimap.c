/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:22:02 by jforner           #+#    #+#             */
/*   Updated: 2022/06/09 18:42:55 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	mmap_print(t_play *p)
{
	int	i;
	int	j;
	int	coord[2];

	i = -1;
	while (++i < 49)
	{
		j = -1;
		while (++j < 49)
		{
			coord[0] = (int)p->posx + ((i / 7) - 3);
			coord[1] = (int)p->posy + ((j / 7) - 3);
			// printf("i = %d\tj = %d\tx = %d\ty = %d\tc = %c\n", i, j, (int)p->posx + ((i / 7) - 3), (int)p->posy + ((j / 7) - 3), p->map[2][21]);
			mmap_color(p, i, j, coord);
		}
	}
}

void	mmap_color(t_play *p, int i, int j, int coord[2])
{
	if (i % 7 == 0 || j % 7 == 0)
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
