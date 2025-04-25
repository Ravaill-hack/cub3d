/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:31:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/25 15:35:49 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_calculate_ray(t_var *var, t_ray *ray, double angle)
{
	t_pix	play;
	double	h_wall;
	double	dist_correction;

	h_wall = 64.0; //wall
	play.x = var->play.pos_x * var->zoom_mnm;
	play.y = var->play.pos_y * var->zoom_mnm;
	ray->angle = fmod(angle - (double)var->play.angle, 360.0);
	dist_correction = cos(ft_deg_to_rad(ray->angle)); 
	ray->target_height = (int)round(((h_wall / ray->target_dist) * var->dist_to_plane) / dist_correction);
	printf("distance : %f, angle_diff: %f, hauteur vue : %d\n", ray->target_dist, ray->angle, ray->target_height);
	return 1;
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
	// end_v.x = play.x + (int)round(var->play.or_x * var->zoom_mnm);
	// end_v.y = play.y + (int)round(var->play.or_y * var->zoom_mnm);
	end_v = ft_find_end(var, or_x, or_y, &(ray->target_dist));
	printf("le mur est intercepte en x = %d, y = %d\n", end_v.x, end_v.y);
	line.pixel_1 = play;
	line.pixel_2 = end_v;
	ft_draw_line_bres(var, line, &(var->mini_map));
	printf("l'angle vaut : %f, ", angle);
	printf("en radians : %f\n", ft_deg_to_rad(angle));
	printf("or_x = %f, or_y = %f\n", or_x, or_y);
	printf("je dessine un rayon allant jusqu'a %d, %d\n", end_v.x, end_v.y);
	printf("la distance est de %f\n\n", ft_distance(play, end_v));
	printf("la distance est de %f\n\n", ray->target_dist);
	return (end_v);
}

int	ft_draw_screen(t_var *var)
{
	double	angle_start;
	double	angle_end;
	double	step_angle;
	int		i;
	t_ray	ray;
	
	angle_start = (double)(fmod(var->play.angle - (var->plane.fov_deg / 2), 360.0));
	angle_end = (double)(fmod(var->play.angle + (var->plane.fov_deg / 2), 360.0));
	step_angle = (double)var->plane.fov_deg / (double)var->win.width;
	i = 0;
	while (i < var->win.width)
	{
		// Dessin dans la minimap
	 	ray.target_node = ft_draw_vector(var, angle_start, &ray);
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
