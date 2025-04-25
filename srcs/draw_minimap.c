/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:31:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/25 11:15:21 by lmatkows         ###   ########.fr       */
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

void	ft_draw_nodes(t_var *var)
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
	// printf("apres arrondi : %d, %d\n", point.x, point.y);
	return (point);
}

t_pix	ft_draw_vector(t_var *var, double angle)
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
	end_v = ft_find_end(var, or_x, or_y);
	line.pixel_1 = play;
	line.pixel_2 = end_v;
	ft_draw_line_bres(var, line, &(var->mini_map));
	// printf("l'angle vaut : %f\n", angle);
	// printf("l'angle vaut : %f\n", ft_deg_to_rad(angle));
	// printf("or_x = %f, or_y = %f\n", or_x, or_y);
	// printf("je dessine un rayon allant jusqu'a %d, %d\n\n", end_v.x, end_v.y);
	return (end_v);
}
// fonctions suivantes a integrer dans un fichier raycasting
int	ft_calculate_ray(t_var *var, t_ray *ray, int angle)
{
	t_pix	play;
	double	h_wall;

	h_wall = 64.0;
	play.x = var->play.pos_x;
	play.y = var->play.pos_y;
	ray->angle = angle;
	ray->target_dist = ft_distance(play, ray->target_node);
	ray->target_height = (int)round((h_wall / ray->target_dist) * var->dist_to_plane);
	//printf("hauteur vue : %d\n", ray->target_height);
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
	column.pixel_2 = top;
	ft_draw_line_bres(var, column, &(var->screen));
	return (1);
}
// fonctions precedentes a integrer dans un fichier raycasting

int	ft_draw_cone(t_var *var)
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
	printf("nb rayons = %d\n", var->win.width);
	while (i < var->win.width)
	{
		// Dessin dans la minimap
	 	ray.target_node = ft_draw_vector(var, angle_start);
	 	// Dessin dans le game screen
		printf("Pour i = %d, ", i);
		if (!ft_calculate_ray(var, &ray, angle_start) || !ft_draw_ray(var, ray, i))
		 	return (ft_err("Error\nRay calculation failed\n"));
		angle_start = (angle_start + step_angle);
		if (angle_start >= 360.0)
			angle_start -= 360.0;
		i++;
	}
	return(1);
}

int	ft_draw_minimap(t_var *var)
{
	ft_draw_nodes(var);
	ft_draw_player(var);
	ft_draw_cone(var);
	return (0);
}
