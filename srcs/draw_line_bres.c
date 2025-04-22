/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:45:26 by julien            #+#    #+#             */
/*   Updated: 2025/04/22 22:18:55 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_bres_sx_sy(t_bresenham *bres, t_line line)
{
	if (line.pixel_1.x < line.pixel_2.x)
		bres->sx = 1;
	else
		bres->sx = -1;
	if (line.pixel_1.y < line.pixel_2.y)
		bres->sy = 1;
	else
		bres->sy = -1;
}

void	ft_update_bres(t_bresenham *bres, t_pixel *pixel)
{
	if (bres->e2 > -bres->dy)
	{
		bres->err -= bres->dy;
		pixel->x += bres->sx;
	}
	if (bres->e2 < bres->dx)
	{
		bres->err += bres->dx;
		pixel->y += bres->sy;
	}
}

void	ft_mlx_pixel_put(t_var *var,
	t_pixel pixel, unsigned int color)
{
	char	*dst;

	dst = var->mini_map.data_addr
		+ (pixel.y * var->mini_map.line_len
			+ pixel.x * (var->mini_map.bit_per_pix / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_line_bres(t_var *var, t_line line)
{
	t_bresenham				bres;

	bres.dx = ft_abs(line.pixel_2.x - line.pixel_1.x);
	bres.dy = ft_abs(line.pixel_2.y - line.pixel_1.y);
	ft_set_bres_sx_sy(&bres, line);
	bres.err = bres.dx - bres.dy;
	while (!(line.pixel_1.x == line.pixel_2.x
			&& line.pixel_1.y == line.pixel_2.y))
	{
		ft_mlx_pixel_put(var, line.pixel_1, 0xFFFFFF);
		bres.e2 = bres.err * 2;
		ft_update_bres(&bres, &line.pixel_1);
	}
	ft_mlx_pixel_put(var, line.pixel_1, line.pixel_2.color);
}

/*
int	ft_line_is_in_screen(t_var *var, t_pixel *pixel_1, t_pixel *pixel_2)
{
	if ((pixel_1->x < 0 && pixel_2->x < 0)
		|| (pixel_1->x >= var->mini_map.width
			&& pixel_2->x >= var->mini_map.width)
		|| (pixel_1->y < 0 && pixel_2->y < 0)
		|| (pixel_1->y >= var->mini_map.height
			&& pixel_2->y >= var->mini_map.height))
		return (0);
	return (1);
}
*/