/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:17:32 by jforner           #+#    #+#             */
/*   Updated: 2022/06/06 17:45:18 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	show_mouse(void)
{
	static int	show = 1;

	if (show)
	{
		mlx_mouse_hide();
		show = 0;
	}
	else
	{
		mlx_mouse_show();
		show = 1;
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
