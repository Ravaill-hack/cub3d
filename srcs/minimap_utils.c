/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:42:18 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 13:16:28 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_close_to_player(t_var *var, int x, int y)
{
	t_pix	player;
	t_pix	point;

	player.x = var->play.pos_x * var->zoom;
	player.y = var->play.pos_y * var->zoom;
	point.x = x;
	point.y = y;
	if (ft_distance(player, point) <= var->step)
		return (1);
	return (0);
}

int	ft_wall_type(double delta_x, double delta_y, char c)
{
	if (c == ' ')
		return (1);
	else if (c == '1')
	{
		if (delta_x >= 0 && delta_x >= fabs(delta_y))
			return (4);
		else if (delta_x <= 0 && (-delta_x) >= fabs(delta_y))
			return (2);
		else if (delta_y >= 0 && delta_y >= fabs(delta_x))
			return (3);
		else if (delta_y <= 0 && (-delta_y) >= fabs(delta_x))
			return (5);
		else
			return (1);
	}
	return (0);
}

int	ft_is_zoom_wall(t_double_points p, t_map *map, int zoom, char c)
{
	int				x_n;
	int				y_n;
	t_double_points	round;
	t_double_points	delta;

	round.x = p.x / (double)zoom;
	round.y = p.y / (double)zoom;
	x_n = floor(round.x);
	y_n = floor(round.y);
	delta.x = round.x - (double)x_n - 0.5;
	delta.y = round.y - (double)y_n - 0.5;
	if (!(round.y >= 0 && round.x >= 0
			&& round.x < map->size_x * zoom && round.y < map->size_y * zoom))
		return (0);
	if (map->tab[y_n][x_n] == c)
	{
		return (ft_wall_type(delta.x, delta.y, c));
	}
	return (0);
}

int	ft_check_wall(double x, double y, t_map *map, int zoom)
{
	int				true_wall;
	int				unseen_wall;
	t_double_points	point;

	point.x = x;
	point.y = y;
	true_wall = ft_is_zoom_wall(point, map, zoom, '1');
	unseen_wall = ft_is_zoom_wall(point, map, zoom, ' ');
	if (true_wall != 0)
		return (true_wall);
	if (unseen_wall)
		return (1);
	return (0);
}

void	ft_draw_player(t_var *var)
{
	t_pix	tmp;

	tmp.y = 0;
	while (tmp.y <= var->map->size_y * var->zoom)
	{
		tmp.x = 0;
		while (tmp.x <= var->map->size_x * var->zoom)
		{
			if (ft_is_close_to_player(var, tmp.x, tmp.y) == 1)
			{
				tmp.x++;
				tmp.y++;
				ft_draw_disc(var, tmp, 0xFF0000, &var->mini_map);
				tmp.x--;
				tmp.y--;
			}
			tmp.x++;
		}
		tmp.y++;
	}
}
