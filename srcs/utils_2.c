/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:35:57 by julien            #+#    #+#             */
/*   Updated: 2025/04/22 18:53:39 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_wall(int x, int y, t_map *map)
{
	if (x < map->size_x && y < map->size_y && map->tab[y][x] == '1')
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
