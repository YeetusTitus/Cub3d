/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:02:54 by jforner           #+#    #+#             */
/*   Updated: 2022/05/31 15:39:02 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	freedom(t_play *play)
{
	free(play->texture);
	if (play->map != NULL)
		ft_malloc_error(play->map, tablen(play->map));
}
