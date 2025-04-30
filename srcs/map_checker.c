/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:04:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/30 13:18:00 by lmatkows         ###   ########.fr       */
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
	int		i;
	int		j;

	i = 0;
	while (map->tab[i])
	{
		j = 0;
		while (map->tab[i][j])
		{
			if (map->tab[i][j] == '0')
			{
				if (!ft_check_if_exists(map, map->tab, i, j + 1)
					|| !ft_check_if_exists(map, map->tab, i + 1, j)
					|| !ft_check_if_exists(map, map->tab, i - 1, j)
					|| !ft_check_if_exists(map, map->tab, i, j - 1))
					return (ft_err(ERR_MAP_BOUND));
			}
			j++;
		}
		i++;
	}
	if (var->map->player == 0)
		return (ft_err(ERR_MAP_NO_PLAY));
	return (1);
}
