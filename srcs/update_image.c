/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/25 11:16:19 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_update_image(t_var *var, t_img *img)
{
	if (img->img_ptr)
	{
		mlx_destroy_image(var->mlx_ptr, img->img_ptr);
		ft_init_img(var, img);
		ft_draw_minimap(var);
		mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
			img->img_ptr, img->off_x, img->off_y);
	}
	return (0);
}
