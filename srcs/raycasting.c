/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:31:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/25 14:30:55 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_calculate_ray(t_var *var, t_ray *ray, double angle)
{
	t_pix	play;
	double	h_wall;
	double	dist_correction;

	h_wall = 64.0;
	play.x = var->play.pos_x * var->zoom_mnm;
	play.y = var->play.pos_y * var->zoom_mnm;
	ray->angle = angle;
	dist_correction = 1;
	// dist_correction = cos((fmod(angle - (double)var->play.angle, 360.0)) * (M_PI / 180.0));
	ray->target_dist = ft_distance(play, ray->target_node);
	ray->target_height = (int)round((h_wall / ray->target_dist) * var->dist_to_plane * dist_correction);
	printf("distance : %f hauteur vue : %d\n", ray->target_dist, ray->target_height);
	return (1);
}

int	ft_draw_ray(t_var *var, t_ray ray, int x)
{
	t_pix	top;
	t_pix	bot;
	t_line	column;

	top.y = (1.0 - var->ratio_horizon) * (var->win.height - ray.target_height);
	top.x = x;
	bot.y = top.y + ray.target_height;
	bot.x = x;
	column.pixel_1 = top;
	column.pixel_2 = bot;
	ft_draw_vertical(var, column, 0xFFFFFF, &(var->screen));
	return (1);
}

int	ft_draw_screen(t_var *var)
{
	double	angle_start;
	double	angle_end;
	double	step_angle;
	int		i;
	t_ray	ray;
	
	angle_start = (double)(((int)(var->play.angle + 360) - (var->plane.fov_deg / 2)) % 360);
	angle_end = (double)(((int)(var->play.angle) + (var->plane.fov_deg / 2)) % 360);
	step_angle = (double)var->plane.fov_deg / (double)var->win.width;
	i = 0;
	while (i < var->win.width)
	{
		// Dessin dans la minimap
	 	ray.target_node = ft_draw_vector(var, angle_start);
	 	// Dessin dans le game screen
		// printf("Pour i = %d, ", i);
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
