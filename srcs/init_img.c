/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:44:20 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/28 21:22:25 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_draw_background(t_var *var, t_img *img)
{
	int	x;
	int	y;
	int	h;

	y = 0;
	h = (int)round((1.0 - var->ratio_horizon) * var->win.height);
	while (y < h)
	{
		x = 0;
		while (x <= var->win.width)
			ft_draw_point(var, x++, y, var->txtr.ce_col, img);
		y++;
	}
	while (y <= var->win.height)
	{
		x = 0;
		while (x <= var->win.width)
			ft_draw_point(var, x++, y, var->txtr.fl_col, img);
		y++;
	}
	return (1);
}

t_img	*ft_init_img(t_var *var, t_img *img)
{
	img->img_ptr = mlx_new_image(var->mlx_ptr, var->win.width, var->win.height);
	img->bit_per_pix = 0;
	img->line_len = 0;
	img->endian = 0;
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bit_per_pix,
			&img->line_len, &img->endian);
	return (img);
}

int	ft_init_background(t_var *var)
{
	ft_init_img(var, &var->screen);
	var->screen.off_x = 0;
	var->screen.off_y = 0;
	ft_draw_background(var, &(var->screen));
	return (1);
}

int	ft_init_screen(t_var *var)
{
	ft_init_background(var);
	ft_init_img(var, &(var->mini_map));
	var->mini_map.off_x = var->win.width - (var->map->size_x + 2)
		* var->zoom_mnm;
	var->mini_map.off_y = var->win.height - (var->map->size_y + 2)
		* var->zoom_mnm;
	ft_build_image(var);
	ft_put_image_to_window(var, &(var->screen));
	ft_put_image_to_window(var, &(var->mini_map));
	return (1);
}
