/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:35:57 by julien            #+#    #+#             */
/*   Updated: 2025/04/25 16:46:24 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_intercept_wall(int x, int y, t_map *map)
{
	if (y < 0 || x < 0 || x >= map->size_x || y >= map->size_y)
		return (1);
	if (ft_is_wall(x, y, map) == 1)
		return (1);
	return (0);
}

int	ft_intercept_unseen_wall(int x, int y, t_map *map)
{
	if (y < 0 || x < 0 || x >= map->size_x || y >= map->size_y)
		return (1);
	if (ft_is_unseen_wall(x, y, map) == 1)
		return (1);
	return (0);
}

int	ft_is_wall(int x, int y, t_map *map) //renvoyer 0 si pas de mur, 1 si N, 2 si N, 3 si E, 4 si W
{
	if (y < 0 || x < 0 || (x < map->size_x && y < map->size_y && map->tab[y][x] == '1'))
		return (1);
	return (0);
}

int	ft_is_unseen_wall(int x, int y, t_map *map)
{
	if (y < 0 || x < 0 || (x < map->size_x && y < map->size_y && map->tab[y][x] == ' '))
		return (1);
	return (0);
}

int	ft_strict_check_wall(double x, double y, t_map *map)
{
	if (ft_intercept_wall(x, y, map) == 1
		|| ft_intercept_unseen_wall(x, y, map) == 1)
		return (1);
	return (0);
}

