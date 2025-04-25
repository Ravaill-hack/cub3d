/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:22:56 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/25 14:24:20 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	printf("l'angle vaut : %f, ", angle);
	printf("en radians : %f\n", ft_deg_to_rad(angle));
	printf("or_x = %f, or_y = %f\n", or_x, or_y);
	printf("je dessine un rayon allant jusqu'a %d, %d\n", end_v.x, end_v.y);
	printf("la distance est de %f\n\n", ft_distance(play, end_v));
	return (end_v);
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
