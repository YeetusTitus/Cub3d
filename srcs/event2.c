/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:17:32 by jforner           #+#    #+#             */
/*   Updated: 2022/06/03 22:31:09 by jforner          ###   ########.fr       */
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
