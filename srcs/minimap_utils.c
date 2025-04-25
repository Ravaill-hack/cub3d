/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:42:18 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/25 17:15:29 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_close_to_player(t_var *var, int x, int y)
{
	t_pix	player;
	t_pix	point;

	player.x = var->play.pos_x * var->zoom_mnm;
	player.y = var->play.pos_y * var->zoom_mnm;
	point.x = x;
	point.y = y;
	if (ft_distance(player, point) <= var->step)
		return (1);
	return (0);
}

int	ft_is_zoom_wall(double x, double y, t_map *map, int zoom, char c)
{
	int	x_n;
	int	y_n;

	x_n = floor(x / (double)zoom);
	y_n = floor(y / (double)zoom);
	x = (int)x;
	y = (int)y;
	if (y < 0 || x < 0 || ((x < map->size_x * zoom) && y < (map->size_y * zoom) && map->tab[y_n][x_n] == c))
		return (1);
	return (0);
}

int	ft_check_wall(double x, double y, t_map *map, int zoom)
{
	if (ft_is_zoom_wall(x, y, map, zoom, '1') == 1
			|| ft_is_zoom_wall(x, y, map, zoom, ' ') == 1
		// || ft_is_zoom_wall(x + 0.25 * zoom, y, map, zoom) == 1
		// || ft_is_zoom_wall(x - 0.25 * zoom, y, map, zoom) == 1
		// || ft_is_zoom_wall(x, y + 0.25 * zoom, map, zoom) == 1
		// || ft_is_zoom_wall(x, y - 0.25 * zoom, map, zoom) == 1
		// || ft_is_zoom_wall(x + 0.25 * zoom, y + 0.25 * zoom, map, zoom) == 1
		// || ft_is_zoom_wall(x - 0.25 * zoom, y + 0.25 * zoom, map, zoom) == 1
		// || ft_is_zoom_wall(x + 0.25 * zoom, y - 0.25 * zoom, map, zoom) == 1
		// || ft_is_zoom_wall(x - 0.25 * zoom, y - 0.25 * zoom, map, zoom) == 1
	)
		return (1);
	return (0);
}

void	ft_draw_player(t_var *var)
{
	int		x;
	int		y;

	y = 0;
	while (y <= var->map->size_y * var->zoom_mnm)
	{
		x = 0;
		while (x <= var->map->size_x * var->zoom_mnm)
		{
			if (ft_is_close_to_player(var, x, y) == 1)
				ft_draw_disc(var, x + 0.5, y + 0.5, 0xFF0000, &var->mini_map);
			x++;
		}
		y++;
	}
}
