/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:17:32 by jforner           #+#    #+#             */
/*   Updated: 2022/06/10 15:17:44 by jforner          ###   ########.fr       */
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

void	ft_pixel_put(t_disp *display, int x, int y, int color)
{
	char	*dst;

	dst = display->addr
		+ (y * display->line_length + x * (display->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
