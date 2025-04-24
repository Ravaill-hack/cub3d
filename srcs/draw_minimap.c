/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:31:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/24 12:32:15 by Lmatkows         ###   ########.fr       */
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

t_pix	ft_find_end(t_var *var, double or_x, double or_y, int angle)
{
	t_pix	point;
	double	x;
	double	y;

	x = var->play.pos_x * var->zoom_mnm;
	y = var->play.pos_y * var->zoom_mnm;
	while (!ft_strict_check_wall(x / var->zoom_mnm, y / var->zoom_mnm, var->map, angle))
	{
		x += or_x;
		y += or_y;	
	}
	point.x = (int)round(x);
	point.y = (int)round(y);
	return (point);
}

// t_pix	ft_find_end(t_var *var, double or_x, double or_y)
// {
// 	t_pix	point;
// 	double	x;
// 	double	y;

// 	x = var->play.pos_x;
// 	y = var->play.pos_y;
// 	while (!ft_strict_check_wall(x , y, var->map))
// 	{
// 		x += or_x;
// 		y += or_y;	
// 	}
// 	point.x = (int)round(x * var->zoom_mnm);
// 	point.y = (int)round(y * var->zoom_mnm);
// 	return (point);
// }

t_pix	ft_draw_vector(t_var *var, double or_x, double or_y, int angle)
{
	t_pix	play;
	t_pix	end_v;
	t_line	line;

	play.x = var->play.pos_x * var->zoom_mnm;
	play.y = var->play.pos_y * var->zoom_mnm;
	// end_v.x = play.x + (int)round(var->play.or_x * var->zoom_mnm);
	// end_v.y = play.y + (int)round(var->play.or_y * var->zoom_mnm);
	end_v = ft_find_end(var, or_x, or_y, angle);
	line.pixel_1 = play;
	line.pixel_2 = end_v;
	ft_draw_line_bres(var, line);
	return (end_v);
}
// fonctions suivantes a integrer dans un fichier raycasting
// int	ft_calculate_ray(t_var *var, t_ray *ray, int angle)
// {
// 	t_pix	play;

// 	play.x = var->play.pos_x;
// 	play.y = var->play.pos_y;
// 	ray->angle = angle;
// 	ray->target_dist = ft_distance(play, ray->target_node);
// 	return (1);
// }

// int	ft_draw_ray(t_var *var, t_ray ray)
// {
	
// }
// fonctions precedentes a integrer dans un fichier raycasting

void	ft_draw_cone(t_var *var)
{
	int		angle_start;
	int		angle_end;
	t_ray	ray;

	angle_start = ((int)(var->play.angle + 360) - 40) % 360;
	angle_end = ((int)(var->play.angle) + 40) % 360;
	while (angle_start != angle_end)
	{
		// Dessin dans la minimap
	 	ray.target_node = ft_draw_vector(var, cos(ft_deg_to_rad(angle_start)),
				sin(ft_deg_to_rad(angle_start)), angle_start);
	 	// Dessin dans le game screen
		// if (!ft_calculate_ray(var, &ray, angle_start) || !ft_draw_ray(var, ray))
		// 	return (ft_err("Error\nRay calculation failed\n"));
		angle_start = (angle_start + 1) % 360;
	}
	(void)ray;
}

int	ft_draw_minimap(t_var *var)
{
	ft_draw_nodes(var);
	ft_draw_player(var);
	ft_draw_cone(var);
	return (0);
}
