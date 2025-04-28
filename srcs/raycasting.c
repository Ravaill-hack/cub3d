/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:31:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/28 21:49:36 by julien           ###   ########.fr       */
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

int	ft_draw_column(t_var *var, t_ray *ray, t_img *img, t_line line)
{
	int		x_txt;
	t_img	*txt;
	double	v_step;
	int		y_txt;
	int		col;
	int		i_y;

	txt = NULL;
	if (ray->wall == 4) // East
	{
		printf("on est a l'Est\n");
		txt = &(var->txtr.ea_img);
		x_txt = ((var->map->size_y - ray->target_node.y)
				* var->zoom_mnm) % txt->width;
	}
	else if (ray->wall == 2) // West
	{
		printf("on est a l'Ouest\n");
		txt = &(var->txtr.we_img);
		printf("txt width = %d \n", txt->width);
		x_txt = (ray->target_node.y * var->zoom_mnm) % txt->width;
	}
	else if (ray->wall == 5) // South
	{
		printf("on est au Sud\n");
		txt = &(var->txtr.so_img);
		x_txt = ((var->map->size_x - ray->target_node.x)
				* var->zoom_mnm) % txt->width;
	}
	else if (ray->wall == 3) // North
	{
		printf("on est au Nord\n");
		txt = &(var->txtr.no_img);
		x_txt = (ray->target_node.x * var->zoom_mnm) % txt->width;
	}
	else
		return (0);
	y_txt = 0;
	i_y = line.pixel_1.y;
	v_step = txt->height / ray->target_height;
	while (y_txt <= txt->height)
	{
		printf("y_txt = %d, x_txt = %d\n", y_txt, x_txt);
		printf("data addr = %p, txt_line_len = %d, txt_bpp %d\n",
			txt->data_addr, txt->line_len, txt->bit_per_pix);
		col = *((int *)(txt->data_addr + y_txt * txt->line_len
					+ (x_txt * txt->bit_per_pix / 8)));
		ft_draw_point(var, line.pixel_1.x, i_y, col, img);
		i_y++;
		y_txt = i_y * v_step;
	}
	return (1);
}

int	ft_draw_ray(t_var *var, t_ray ray, int x)
{
	t_pix	top;
	t_pix	bot;
	t_line	column;

	top.y = (1.0 - var->ratio_horizon) * (var->win.height - ray.target_height);
	top.x = x;
	if (ray.wall == 1)
		top.col = 0xFF0000;
	else if (ray.wall == 2)
		top.col = 0xFFFF00;
	else if (ray.wall == 3)
		top.col = 0x00FF00; //ici
	else if (ray.wall == 4)
		top.col = 0x00FFFF; //ici
	else if (ray.wall == 5)
		top.col = 0x0000FF;
	bot.y = top.y + ray.target_height;
	bot.x = x;
	column.pixel_1 = top;
	column.pixel_2 = bot;
	top.col = ft_darker_pix(top.col, ray.target_dist);
	ft_draw_column(var, &ray, &(var->screen), column);
	//ft_draw_vertical(var, column, top.col, &(var->screen));
	return (1);
}

int	ft_draw_vector(t_var *var, double angle, t_ray *ray)
{
	t_pix	play;
	t_line	line;
	double	or_x;
	double	or_y;

	or_x = cos(ft_deg_to_rad(angle));
	or_y = sin(ft_deg_to_rad(angle));
	play.x = var->play.pos_x * var->zoom_mnm;
	play.y = var->play.pos_y * var->zoom_mnm;
	ft_find_end(var, or_x, or_y, ray);
	line.pixel_1 = play;
	line.pixel_2 = ray->target_node;
	ft_draw_line_bres(var, line, &(var->mini_map));
	return (1);
}

int	ft_draw_screen(t_var *var)
{
	double	angle_start;
	double	step_angle;
	int		i;
	t_ray	ray;

	angle_start = (double)(fmod(var->play.angle
				- (var->plane.fov_deg / 2), 360.0));
	step_angle = (double)var->plane.fov_deg / (double)var->win.width;
	i = 0;
	while (i < var->win.width)
	{
		if (!ft_draw_vector(var, angle_start, &ray)
			|| !ft_calculate_ray(var, &ray, angle_start)
			|| !ft_draw_ray(var, ray, i))
			return (ft_err("Error\nRay calculation failed\n"));
		angle_start = fmod(angle_start + step_angle, 360.0);
		i++;
	}
	return (1);
}
