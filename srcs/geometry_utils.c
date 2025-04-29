/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:25:59 by julien            #+#    #+#             */
/*   Updated: 2025/04/29 11:39:38 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_find_orientation(t_var *var)
{
	var->play.or_x = cos((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	var->play.or_y = sin((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	return (0);
}

double	ft_distance(t_pix p1, t_pix p2)
{
	double	dist;
	double	delta_x;
	double	delta_y;

	delta_x = (double)(p2.x - p1.x);
	delta_y = (double)(p2.y - p1.y);
	dist = sqrtf(delta_y * delta_y + delta_x * delta_x);
	return (dist);
}

double	ft_distance_double(double x1, double y1, double x2, double y2)
{
	double	dist;
	double	delta_x;
	double	delta_y;

	delta_x = (x2 - x1);
	delta_y = (y2 - y1);
	dist = sqrt(delta_y * delta_y + delta_x * delta_x);
	return (dist);
}

double	ft_deg_to_rad(double angle_deg)
{
	return (angle_deg * M_PI / 180.0);
}

int	ft_find_end(t_var *var, double or_x, double or_y, t_ray *ray)
{
	t_end	end;

	end.x_st = var->play.pos_x * var->zoom;
	end.y_st = var->play.pos_y * var->zoom;
	end.x = end.x_st;
	end.y = end.y_st;
	ray->wall = 0;
	while (!ray->wall)
	{
		end.x += or_x;
		end.y += or_y;
		ray->wall = ft_check_wall(end.x, end.y, var->map, var->zoom);
	}
	while (ray->wall != 0)
	{
		end.tmp = ray->wall;
		end.x -= (or_x / 20.0);
		end.y -= (or_y / 20.0);
		ray->wall = ft_check_wall(end.x, end.y, var->map, var->zoom);
	}
	ray->wall = end.tmp;
	ray->target_dist = ft_distance_double(end.x_st, end.y_st, end.x, end.y);
	ray->t_node.x = (int)round(end.x);
	ray->t_node.y = (int)round(end.y);
	return (1);
}
