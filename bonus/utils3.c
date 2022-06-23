/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:58:07 by jforner           #+#    #+#             */
/*   Updated: 2022/06/23 17:01:06 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_win(t_play *p)
{
	p->mouse = 1;
	p->keys.w = 1;
	p->keys.s = 1;
	p->keys.a = 1;
	p->keys.d = 1;
	p->keys.right = 1;
	p->keys.left = 1;
	p->showmap = 0;
	p->xmouse = (SCREENWIDTH / 2);
	p->win = mlx_new_window(p->mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	p->disp.img = mlx_new_image(p->mlx, SCREENWIDTH, SCREENHEIGHT);
	p->mmap.img = mlx_new_image(p->mlx, (((7 * SCREENWIDTH) / 400) * 7) + 1,
			(((7 * SCREENHEIGHT) / 200) * 7) + 1);
	p->disp.addr = mlx_get_data_addr(p->disp.img, &p->disp.bits_per_pixel,
			&p->disp.line_length, &p->disp.endian);
	p->mmap.addr = mlx_get_data_addr(p->mmap.img, &p->mmap.bits_per_pixel,
			&p->mmap.line_length, &p->mmap.endian);
}

void	ft_pixel_put(t_disp *display, int x, int y, int color)
{
	char	*dst;

	dst = display->addr
		+ (y * display->line_length + x * (display->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_data_color(int x, int y, t_disp disp)
{
	char	*dst;

	dst = disp.addr + (y * disp.line_length + x * (disp.bits_per_pixel / 8));
	return (*(int *)dst);
}

void	get_floorwall(t_play *p, int h, int *y)
{
	if (p->drawend + 1 == h && p->drawstart == 0)
		*y = h;
	else
		*y = p->drawend;
	if (p->side == 0)
	{
		p->floorxwall = p->mapx;
		p->floorywall = p->mapy + p->wallx;
		if (p->raydirx < 0)
			p->floorxwall = p->mapx + 1.0;
	}
	else if (p->side == 1)
	{
		p->floorxwall = p->mapx + p->wallx;
		p->floorywall = p->mapy;
		if (p->raydiry < 0)
			p->floorywall = p->mapy + 1.0;
	}
}

char	*tjoin(char	**tab)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = -1;
	len = 0;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			len++;
	}
	str = (char *)malloc((sizeof(char) * len) + 1);
	i = tablen(tab);
	str[len] = '\0';
	while (--i >= 0)
	{
		j = ft_strlen(tab[i]);
		while (--j >= 0)
			str[--len] = tab[i][j];
	}
	free(tab[0]);
	tab[0] = str;
	return (str);
}

