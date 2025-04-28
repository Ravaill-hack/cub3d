/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:31:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/28 10:32:56 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_calculate_ray(t_var *var, t_ray *ray, double angle)
{
	double	h_wall;
	double	dist_correction;

	h_wall = 64.0;
	ray->angle = fmod(angle - (double)var->play.angle, 360.0);
	dist_correction = cos(ft_deg_to_rad(ray->angle)); 
	ray->target_height = (int)round(((h_wall / ray->target_dist)
			* var->dist_to_plane) / dist_correction);
	return (1);
}


int	ft_draw_ray(t_var *var, t_ray ray, int x)
{
	t_pix	top;
	t_pix	bot;
	t_line	column;

	top.y = (1.0 - var->ratio_horizon) * (var->win.height - ray.target_height);
	top.x = x;
	top.col = 0xFFFFFF;
	bot.y = top.y + ray.target_height;
	bot.x = x;
	column.pixel_1 = top;
	column.pixel_2 = bot;
	top.col = ft_darker_pix(top.col, ray.target_dist);
	ft_draw_vertical(var, column, top.col, &(var->screen));
	return (1);
}

t_pix	ft_draw_vector(t_var *var, double angle, t_ray *ray)
{
	t_pix	play;
	t_pix	end_v;
	t_line	line;
	double	or_x;
	double	or_y;

	or_x = cos(ft_deg_to_rad(angle));
	or_y = sin(ft_deg_to_rad(angle));
	play.x = var->play.pos_x * var->zoom_mnm;
	play.y = var->play.pos_y * var->zoom_mnm;
	end_v = ft_find_end(var, or_x, or_y, ray);
	line.pixel_1 = play;
	line.pixel_2 = end_v;
	ft_draw_line_bres(var, line, &(var->mini_map));
	return (end_v);
}

int	ft_draw_screen(t_var *var)
{
	double	angle_start;
	double	step_angle;
	int		i;
	t_ray	ray;
	
	angle_start = (double)(fmod(var->play.angle - (var->plane.fov_deg / 2), 360.0));
	step_angle = (double)var->plane.fov_deg / (double)var->win.width;
	i = 0;
	while (i < var->win.width)
	{
	 	ray.target_node = ft_draw_vector(var, angle_start, &ray);
		if (!ft_calculate_ray(var, &ray, angle_start) || !ft_draw_ray(var, ray, i))
		 	return (ft_err("Error\nRay calculation failed\n"));
		angle_start = fmod(angle_start + step_angle, 360.0);
		i++;
	}
	return(1);
}

int	ft_build_image(t_var *var)
{
	ft_draw_nodes(var);
	ft_draw_player(var);
	ft_draw_screen(var);
	return (0);
}
