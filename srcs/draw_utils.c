/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:45:08 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/28 21:25:57 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_point(t_var *var, int x, int y, int col, t_img *img)
{
	char	*ptr;

	if (x < 0 || x >= var->win.width || y < 0 || y >= var->win.height)
		return ;
	ptr = img->data_addr + (y * img->line_len) + x * (img->bit_per_pix / 8);
	*(int *)ptr = col;
}

void	ft_draw_line_map(t_var *var, t_img *img, t_pix p1, t_pix p2, int col)
{
	int		x;
	int		y;

	x = p1.x;
	y = p1.y;
	if (x == p2.x)
	{
		while (y != p2.y)
		{
			ft_draw_point(var, x, y, col, img);
			y++;
		}
	}
	else if (y == p2.y)
	{
		while (x != p2.x)
		{
			ft_draw_point(var, x, y, col, img);
			x++;
		}
	}
	else
		printf("Error\nUnable to draw minimap boundaries\n");
}

void	ft_draw_disc(t_var *var, int x0, int y0, int col, t_img *img)
{
	int		r;
	int		x;
	int		y;
	int		angle;

	r = var->zoom_mnm / 4;
	while (r > 0)
	{
		angle = 0;
		while (angle <= 360)
		{
			x = x0 + cos(ft_deg_to_rad(angle)) * r;
			y = y0 + sin(ft_deg_to_rad(angle)) * r;
			ft_draw_point(var, x, y, col, img);
			angle ++;
		}
		r--;
	}
}

void	ft_init_points(t_pix *p0, t_pix *p1, t_pix *p2, t_pix *p3,
		t_var *var, int x, int y)
{
	p0->x = x * var->zoom_mnm;
	p0->y = y * var->zoom_mnm;
	p1->x = p0->x + var->zoom_mnm;
	p1->y = p0->y;
	p2->x = p0->x;
	p2->y = p0->y + var->zoom_mnm;
	p3->x = p0->x + var->zoom_mnm;
	p3->y = p0->y + var->zoom_mnm;
}

void	ft_connect_nodes(t_var *var, t_img *img, int x, int y, int col)
{
	t_pix	p0;
	t_pix	p1;
	t_pix	p2;
	t_pix	p3;

	ft_init_points(&p0, &p1, &p2, &p3, var, x, y);
	if (ft_is_wall(x, y, var->map) == 1)
	{
		if (p1.x <= var->map->size_x * var->zoom_mnm)
		{
			ft_draw_line_map(var, img, p0, p1, col);
			if (p2.y <= var->map->size_y * var->zoom_mnm)
				ft_draw_line_map(var, img, p2, p3, col);
		}
		if (p2.y <= var->map->size_y * var->zoom_mnm)
		{
			ft_draw_line_map(var, img, p0, p2, col);
			if (p3.x <= var->map->size_x * var->zoom_mnm)
				ft_draw_line_map(var, img, p1, p3, col);
		}
	}
}
