/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:42:18 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/28 11:00:38 by lmatkows         ###   ########.fr       */
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
	// 2 = W
	// 3 = N
	// 4 = E
	// 5 = S
	int		x_n;
	int		y_n;
	int		round_x;
	int		round_y;
	double	delta_x;
	double	delta_y;

	printf("x = %f, y = %f\n", x, y);
	round_x = x / (double)zoom;
	round_y = y / (double)zoom;
	x_n = floor(round_x);
	y_n = floor(round_y);
	delta_x = round_x - x_n;
	delta_y = round_y - y_n;
	if (round_y < 0 || round_x < 0 || ((round_x < map->size_x * zoom) && round_y < (map->size_y * zoom) && map->tab[y_n][x_n] == c))
	{
		if (c == ' ')
			return (1);
		else if (c == '1')
		{
			if ((delta_x >= 0 && delta_x <= 0.5) && (delta_y >= -0.5 && delta_y <= 0.5))
				return (4);
			else if ((delta_x >= -0.5 && delta_x < 0) && (delta_y >= -0.5 && delta_y <= 0.5))
				return (2);
		}
	}
	return (0);
}

int	ft_check_wall(double x, double y, t_map *map, int zoom)
{
	int	true_wall;
	int	unseen_wall;

	true_wall = ft_is_zoom_wall(x, y, map, zoom, '1');
	unseen_wall = ft_is_zoom_wall(x, y, map, zoom, ' ');
	if (true_wall)
		return (true_wall);
	if (unseen_wall)
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
