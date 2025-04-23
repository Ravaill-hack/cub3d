/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:04:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/23 15:42:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_nb_char(char **tab, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == c)
				count ++;
			j++;
		}
		i++;
	}
	return (count);
}

int	ft_check_if_exists(t_map *map, char **tab, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->size_x || y >= map->size_y || !tab[x][y]
		|| (tab[x][y] != '0' && tab[x][y] != '1'))
		return (0);
	return(1);
}

int	ft_is_valid_map(t_map *map, t_var *var)
{
	char **tab;
	int	i;
	int j;

	i = 0;
	(void)var;
	tab = map->tab;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '0')
			{
				if (! ft_check_if_exists(map, tab, i, j + 1)
					|| !ft_check_if_exists(map, tab, i + 1, j)
					|| !ft_check_if_exists(map, tab, i - 1, j)
					|| !ft_check_if_exists(map, tab, i, j - 1))
					return (ft_putstr_fd("Error\nA wall is open on the boundaries\n", 2), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
