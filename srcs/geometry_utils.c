/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:25:59 by julien            #+#    #+#             */
/*   Updated: 2025/04/25 14:22:37 by lmatkows         ###   ########.fr       */
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

double	ft_deg_to_rad(double angle_deg)
{
	return (angle_deg * M_PI / 180.0);
}

t_pix	ft_find_end(t_var *var, double or_x, double or_y)
{
	t_pix	point;
	double	x;
	double	y;

	x = var->play.pos_x * var->zoom_mnm;
	y = var->play.pos_y * var->zoom_mnm;
	while (!ft_strict_check_wall(x / var->zoom_mnm, y / var->zoom_mnm, var->map))
	{
		x += or_x;
		y += or_y;	
	}
	point.x = (int)round(x);
	point.y = (int)round(y);
	return (point);
}
