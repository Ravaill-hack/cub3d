/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 20:14:28 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_update_image(t_var *var, t_img *img)
{
	int	off_x;
	int	off_y;

	off_x = var->win.width - (var->map->size_x + 2) * var->zoom_mnm;
	off_y = var->win.height - (var->map->size_y + 2) * var->zoom_mnm;
	if (img->img_ptr)
	{
		mlx_destroy_image(var->mlx_ptr, img->img_ptr);
		ft_init_img(var, &(var->mini_map));
		ft_draw_minimap(var);
		mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
			img->img_ptr, off_x, off_y);
	}
	return (0);
}
