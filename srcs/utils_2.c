/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:35:57 by julien            #+#    #+#             */
/*   Updated: 2025/04/24 13:32:57 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_intercept_wall(int x, int y, t_map *map, int angle)
{
	if (y < 0 || x < 0 || x >= map->size_x || y >= map->size_y)
		return (1);
	if (angle == 45)
	{
		if (ft_is_wall(x - 1, y, map) && ft_is_wall(x, y + 1, map))
			return(1);
	}
	else if (angle == 135)
	{
		if (ft_is_wall(x + 1, y, map) && ft_is_wall(x, y + 1, map))
			return(1);
	}
	else if (angle == 225)
	{
		if (ft_is_wall(x, y - 1, map) && ft_is_wall(x + 1, y, map))
			return(1);
	}
	else if (angle == 315)
	{
		if (ft_is_wall(x - 1, y, map) && ft_is_wall(x, y - 1, map))
			return(1);
	}
	if (ft_is_wall(x, y, map) == 1)
		return (1);
	return (0);
}

int	ft_intercept_unseen_wall(int x, int y, t_map *map, int angle)
{
	if (y < 0 || x < 0 || x >= map->size_x || y >= map->size_y)
		return (1);
	if (angle == 45)
	{
		if (ft_is_unseen_wall(x - 1, y, map) && ft_is_unseen_wall(x, y + 1, map))
			return(1);
	}
	else if (angle == 135)
	{
		if (ft_is_unseen_wall(x + 1, y, map) && ft_is_unseen_wall(x, y + 1, map))
			return(1);
	}
	else if (angle == 225)
	{
		if (ft_is_unseen_wall(x, y - 1, map) && ft_is_unseen_wall(x + 1, y, map))
			return(1);
	}
	else if (angle == 315)
	{
		if (ft_is_unseen_wall(x - 1, y, map) && ft_is_unseen_wall(x, y - 1, map))
			return(1);
	}
	if (ft_is_unseen_wall(x, y, map) == 1)
		return (1);
	return (0);
}

int	ft_is_wall(int x, int y, t_map *map)
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

double	ft_deg_to_rad(int angle_deg)
{
	return ((double)angle_deg * 2.0 * M_PI / 360.0);
}

int	ft_min(int x1, int x2)
{
	if (x1 <= x2)
		return (x1);
	return (x2);
}

int	ft_max(int x1, int x2)
{
	if (x1 > x2)
		return (x1);
	return (x2);
}

double	ft_distance(t_pix p1, t_pix p2)
{
	double	dist;
	int		delta_x;
	int		delta_y;

	delta_x = ft_max(p1.x, p2.x) - ft_min(p1.x, p2.x);
	delta_y = ft_max(p1.y, p2.y) - ft_min(p1.y, p2.y);
	dist = sqrtf(pow((double)delta_y, 2.0) + pow((double)delta_x, 2.0));
	return (dist);
}
