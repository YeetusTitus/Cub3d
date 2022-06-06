/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:22:11 by jforner           #+#    #+#             */
/*   Updated: 2022/06/06 15:49:53 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_puterror(int argc, t_play *play)
{
	ft_putstr_fd("Error\n", 2);
	if (argc != 2)
		ft_putstr_fd("Put the path of one map on the argument !", 2);
	else if (play->error != '0')
	{
		if (play->error == '1')
			ft_putstr_fd("The map is not close !", 2);
		if (play->error == 'P')
			ft_putstr_fd("The number of player is not correct !", 2);
		if (play->error == 'C')
			ft_putstr_fd("Wrong character in a map", 2);
		if (play->error == 'N')
			ft_putstr_fd("No character in the file", 2);
		if (play->error == 'F')
			ft_putstr_fd("Not the good extension", 2);
		if (play->error == 'I')
			ft_putstr_fd("Invalid information(s) in options", 2);
		if (play->error == 'O')
			ft_putstr_fd("Incorrect number of options", 2);
	}
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	freedom(play);
	return (1);
}

int	fileverif(t_play *play, char *str, int fd, char c)
{
	int		i;

	i = -1;
	while (c == 'c' && str[++i])
	{
		if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u'
			&& str[i + 3] == 'b' && str[i + 4] == '\0')
			return (0);
	}
	while (c == 'x' && str[++i])
	{
		if (str[i] == '.' && str[i + 1] == 'x' && str[i + 2] == 'p'
			&& str[i + 3] == 'm' && str[i + 4] == '\0')
			return (0);
	}
	play->error = 'F';
	close(fd);
	return (1);
}
