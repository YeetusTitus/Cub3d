/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:52:28 by jforner           #+#    #+#             */
/*   Updated: 2022/05/24 10:49:50 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	checkchr(const char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (0);
		i++;
	}
	if (str[i] == ch)
		return (0);
	return (1);
}

char	*ft_strjoin_v2(char *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[len] = 0;
	free(s1);
	return (str);
}

char	*ft_cat(int fd)
{
	char	buff[2];
	char	*line;
	int		error;

	if (fd < 0)
		return (NULL);
	error = 1;
	line = malloc(1);
	line[0] = 0;
	buff[1] = 0;
	while (error)
	{
		error = read(fd, buff, 1);
		if (error == -1)
		{
			free(line);
			return (NULL);
		}
		line = ft_strjoin_v2(line, buff);
	}
	return (line);
}
