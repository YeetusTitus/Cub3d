/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:56:28 by jforner           #+#    #+#             */
/*   Updated: 2022/06/03 21:18:25 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	freedom(t_play *play)
{
	free(play->texture);
	if (play->map != NULL)
		ft_malloc_error(play->map, tablen(play->map));
}

int	split_len2(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (str[++j])
	{
		if (!is_space(str[j]) && str[j + 1] && is_space(str[j + 1]))
			i++;
		if (!j && is_space(str[j]))
			i++;
	}
	return (i);
}

void	strlen2(char *str, int *k)
{
	while (str[*k] && is_space(str[*k]))
		(*k)++;
}

void	splitage2(char *str, char **tabl, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < len)
	{
		k = 0;
		while (!is_space(str[j]))
			j++;
		strlen2(&str[j], &k);
		tabl[i] = ft_substr(str, j, k);
		j += k;
		i++;
	}
	tabl[i] = NULL;
}

char	**split_v2(char *str)
{
	char	**tabl;
	int		len;

	len = split_len2(str);
	tabl = (char **)malloc((sizeof(char *) * len) + 1);
	if (!tabl)
		return (NULL);
	splitage2(str, tabl, len);
	return (tabl);
}
