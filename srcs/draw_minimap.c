/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:31:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/22 18:33:13 by julien           ###   ########.fr       */
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

void	ft_draw_nodes(t_var *var, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y <= var->map->size_y)
	{
		x = 0;
		while (x <= var->map->size_x)
		{
			ft_connect_nodes(var, &var->mini_map, x, y, 0x0000FF);
			x++;
		}
		y++;
	}
}

void	ft_draw_player(t_var *var, t_img *img)
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

int	ft_draw_minimap(t_var *var)
{
	int		x;
	int		y;
	int		col;

	ft_draw_nodes(var, &var->mini_map);
	ft_draw_player(var, &var->mini_map);
	return (0);
}
