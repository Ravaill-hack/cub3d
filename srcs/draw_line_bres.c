/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:45:26 by julien            #+#    #+#             */
/*   Updated: 2025/04/25 11:13:13 by lmatkows         ###   ########.fr       */
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

void	ft_update_bres(t_bresenham *bres, t_pix *pixel)
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

void	ft_draw_horizontal(t_var *var, t_line line, int col, t_img *img)
{
	int	x_min;
	int	x_max;

	x_min = ft_min(line.pixel_1.x, line.pixel_2.x);
	x_max = ft_max(line.pixel_1.x, line.pixel_2.x);
	while(x_min <= x_max)
	{
		ft_draw_point(var, x_min, line.pixel_1.y, col, img);
		x_min++;
	}
}

void	ft_draw_vertical(t_var *var, t_line line, int col, t_img *img)
{
	int	y_min;
	int	y_max;

	y_min = ft_min(line.pixel_1.y, line.pixel_2.y);
	y_max = ft_max(line.pixel_1.y, line.pixel_2.y);
	while(y_min <= y_max)
	{
		ft_draw_point(var, line.pixel_1.x, y_min, col, img);
		y_min++;
	}
}

void	ft_draw_line_bres(t_var *var, t_line line, t_img *img)
{
	t_bresenham				bres;

	bres.dx = ft_abs(line.pixel_2.x - line.pixel_1.x);
	bres.dy = ft_abs(line.pixel_2.y - line.pixel_1.y);
	if (bres.dx <= 1)
		ft_draw_vertical(var, line, 0xFFFFFF, img);
	else if (bres.dy <= 1)
		ft_draw_horizontal(var, line, 0xFFFFFF, img);
	else
	{
		ft_set_bres_sx_sy(&bres, line);
		bres.err = bres.dx - bres.dy;
		while (!(line.pixel_1.x == line.pixel_2.x
				&& line.pixel_1.y == line.pixel_2.y))
		{
			ft_draw_point(var, line.pixel_1.x, line.pixel_1.y, 0xFFFFFF, img);
			bres.e2 = bres.err * 2;
			ft_update_bres(&bres, &line.pixel_1);
		}
		ft_draw_point(var, line.pixel_1.x, line.pixel_1.y, 0xFFFFFF, img);
	}
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