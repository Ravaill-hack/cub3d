/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:45:08 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 12:58:31 by lmatkows         ###   ########.fr       */
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

void	ft_draw_line_map(t_var *var, t_img *img, t_pix p1, t_pix p2, int col)
{
	t_line	line;
	int		x;
	int		y;

	x = p1.x;
	y = p1.y;
	line.pixel_1 = p1;
	line.pixel_2 = p2;
	if (x == p2.x)
		ft_draw_vertical(var, line, col, img);
	else if (y == p2.y)
		ft_draw_horizontal(var, line, col, img);
	else
		printf("Error\nUnable to draw minimap boundaries\n");
}

void	ft_draw_disc(t_var *var, int x0, int y0, int col, t_img *img)
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
			p.x = x0 + cos(ft_deg_to_rad(angle)) * r;
			p.y = y0 + sin(ft_deg_to_rad(angle)) * r;
			ft_draw_point(var, p, col, img);
			angle ++;
		}
		r--;
	}
}

void	ft_init_points(t_pix *p0, t_pix *p1, t_pix *p2, t_pix *p3,
		t_var *var, int x, int y)
{
	p0->x = x * var->zoom;
	p0->y = y * var->zoom;
	p1->x = p0->x + var->zoom;
	p1->y = p0->y;
	p2->x = p0->x;
	p2->y = p0->y + var->zoom;
	p3->x = p0->x + var->zoom;
	p3->y = p0->y + var->zoom;
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
		if (p1.x <= var->map->size_x * var->zoom)
		{
			ft_draw_line_map(var, img, p0, p1, col);
			if (p2.y <= var->map->size_y * var->zoom)
				ft_draw_line_map(var, img, p2, p3, col);
		}
		if (p2.y <= var->map->size_y * var->zoom)
		{
			ft_draw_line_map(var, img, p0, p2, col);
			if (p3.x <= var->map->size_x * var->zoom)
				ft_draw_line_map(var, img, p1, p3, col);
		}
	}
}
