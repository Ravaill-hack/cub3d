/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:25:59 by julien            #+#    #+#             */
/*   Updated: 2025/04/28 21:49:58 by julien           ###   ########.fr       */
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
	double	x;
	double	y;
	double	x_start;
	double	y_start;
	int		tmp;

	x_start = var->play.pos_x * var->zoom_mnm;
	y_start = var->play.pos_y * var->zoom_mnm;
	x = x_start;
	y = y_start;
	ray->wall = 0;
	while (!ray->wall)
	{
		x += or_x;
		y += or_y;
		ray->wall = ft_check_wall(x, y, var->map, var->zoom_mnm);
	}
	while (ray->wall != 0)
	{
		tmp = ray->wall;
		x -= (or_x / 20.0);
		y -= (or_y / 20.0);
		ray->wall = ft_check_wall(x, y, var->map, var->zoom_mnm);
	}
	ray->wall = tmp;
	ray->target_dist = ft_distance_double(x_start, y_start, x, y);
	ray->target_node.x = (int)round(x);
	ray->target_node.y = (int)round(y);
	return (1);
}

// t_pix	ft_find_end(t_var *var, double or_x, double or_y, double *dist)
// {
// 	t_pix	end;
// 	double	x;
// 	double	y;
// 	double	x_start;
// 	double	y_start;

// 	x_start = var->play.pos_x * var->zoom_mnm;
// 	y_start = var->play.pos_y * var->zoom_mnm;
// 	x = x_start;
// 	y = y_start;
// 	while (!ft_strict_check_wall(x / var->zoom_mnm,
//	y / var->zoom_mnm, var->map))
// 	{
// 		x += or_x;
// 		y += or_y;	
// 	}
// 	(*dist) = ft_distance_double(x_start, y_start, x, y);
// 	end.x = (int)round(x);
// 	end.y = (int)round(y);
// 	return (end);
// }
