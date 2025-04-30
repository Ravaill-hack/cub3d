/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:04:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/30 09:37:07 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_if_exists(t_map *map, char **tab, int i, int j)
{
	if (i < 0 || j < 0 || j >= map->size_x || i >= map->size_y || !tab[i][j]
		|| (tab[i][j] != '0' && tab[i][j] != '1'))
		return (0);
	return (1);
}

int	ft_is_valid_map(t_map *map, t_var *var)
{
	char	**tab;
	int		i;
	int		j;

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
				if (!ft_check_if_exists(map, tab, i, j + 1)
					|| !ft_check_if_exists(map, tab, i + 1, j)
					|| !ft_check_if_exists(map, tab, i - 1, j)
					|| !ft_check_if_exists(map, tab, i, j - 1))
					return (ft_err(ERR_MAP_BOUND));
			}
			j++;
		}
		i++;
	}
	return (1);
}
