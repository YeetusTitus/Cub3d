/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:17:32 by jforner           #+#    #+#             */
/*   Updated: 2022/06/13 14:00:51 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	show_mouse(t_play *play)
{
	if (play->mouse)
	{
		mlx_mouse_hide();
		play->mouse = 0;
	}
	else
	{
		mlx_mouse_show();
		play->mouse = 1;
	}
	return (0);
}

int	show_mmmap(t_play *play)
{
	if (play->showmap)
		play->showmap = 0;
	else
		play->showmap = 1;
	mmap_print(play, play->showmap);
	mlx_put_image_to_window(play->mlx, play->win, play->mmap.img, 20, 20);
	return (0);
}

void	ft_pixel_put(t_disp *display, int x, int y, int color)
{
	char	*dst;

	dst = display->addr
		+ (y * display->line_length + x * (display->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
