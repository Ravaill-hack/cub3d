/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:45:08 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 13:19:07 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_point(t_var *var, t_pix p, int col, t_img *img)
{
	char	*ptr;

	if (p.x < 0 || p.x >= var->win.width || p.y < 0 || p.y >= var->win.height)
		return ;
	ptr = img->data_addr + (p.y * img->line_len) + p.x * (img->bit_per_pix / 8);
	*(int *)ptr = col;
}

void	ft_draw_line_map(t_var *var, t_img *img, t_line line, int col)
{
	int		x;
	int		y;

	x = line.pixel_1.x;
	y = line.pixel_1.y;
	if (x == line.pixel_2.x)
		ft_draw_vertical(var, line, col, img);
	else if (y == line.pixel_2.y)
		ft_draw_horizontal(var, line, col, img);
	else
		printf("Error\nUnable to draw minimap boundaries\n");
}

void	ft_draw_disc(t_var *var, t_pix p0, int col, t_img *img)
{
	t_pix	p;
	int		r;
	int		angle;

	r = var->zoom / 4;
	while (r > 0)
	{
		angle = 0;
		while (angle <= 360)
		{
			p.x = p0.x + cos(ft_deg_to_rad(angle)) * r;
			p.y = p0.y + sin(ft_deg_to_rad(angle)) * r;
			ft_draw_point(var, p, col, img);
			angle ++;
		}
		r--;
	}
}

void	ft_init_points(t_angles *a, t_var *var, int x, int y)
{
	a->p0.x = x * var->zoom;
	a->p0.y = y * var->zoom;
	a->p1.x = a->p0.x + var->zoom;
	a->p1.y = a->p0.y;
	a->p2.x = a->p0.x;
	a->p2.y = a->p0.y + var->zoom;
	a->p3.x = a->p0.x + var->zoom;
	a->p3.y = a->p0.y + var->zoom;
}

void	ft_connect_nodes(t_var *var, t_img *img, t_pix n, int col)
{
	t_angles	a;

	ft_init_points(&a, var, n.x, n.y);
	if (ft_is_wall(n.x, n.y, var->map) == 1)
	{
		if (a.p1.x <= var->map->size_x * var->zoom)
		{
			ft_draw_line_map(var, img, ft_build_line(a.p0, a.p1), col);
			if (a.p2.y <= var->map->size_y * var->zoom)
				ft_draw_line_map(var, img, ft_build_line(a.p2, a.p3), col);
		}
		if (a.p2.y <= var->map->size_y * var->zoom)
		{
			ft_draw_line_map(var, img, ft_build_line(a.p0, a.p2), col);
			if (a.p3.x <= var->map->size_x * var->zoom)
				ft_draw_line_map(var, img, ft_build_line(a.p1, a.p3), col);
		}
	}
}
