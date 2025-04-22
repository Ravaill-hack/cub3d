/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:44:20 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 16:42:26 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_init_img(t_var *var, t_img *img)
{
	img->img_ptr = mlx_new_image(var->mlx_ptr, var->win.width, var->win.height);
	img->bit_per_pix = 0;
	img->line_len = 0;
	img->endian = 0;
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bit_per_pix, &img->line_len, &img->endian);
	return (img);
}

int	ft_min(int x1, int x2)
{
	if (x1 <= x2)
		return (x1);
	return (x2);
}

int	ft_max(int x1, int x2)
{
	if (x1 > x2)
		return (x1);
	return (x2);
}

double ft_distance(t_pix p1, t_pix p2)
{
	double	dist;
	int	delta_x;
	int	delta_y;

	delta_x = ft_max(p1.x, p2.x) - ft_min(p1.x, p2.x);
	delta_y = ft_max(p1.y, p2.y) - ft_min(p1.y, p2.y);
	dist = sqrtf(pow((double)delta_y, 2.0) + pow((double)delta_x, 2.0));
	return (dist);
}

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

int	ft_draw_minimap(t_var *var)
{
	int		x;
	int		y;
	int		col;

	y = 0;
	x = 0;
	col = 0x0000FF;
	while (y <= var->map->size_y)
	{
		x = 0;
		while (x <= var->map->size_x)
		{
			ft_connect_nodes(var, &var->mini_map, x, y, col);
			x++;
		}
		y++;
	}
	y = 0;
	while (y <= var->map->size_y * var->zoom_mnm)
	{
		x = 0;
		while (x <= var->map->size_x * var->zoom_mnm)
		{
			if (ft_is_close_to_player(var, x, y) == 1)
				ft_draw_disc(var, x + 0.5, y + 0.5, 0xFF0000, &var->mini_map);
			x ++;
		}
		y ++;
	}
	return (0);
}
