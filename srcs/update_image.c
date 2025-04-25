/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/25 11:40:26 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_put_image_to_window(t_var *var, t_img *img)
{
	mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
		img->img_ptr, img->off_x, img->off_y);
	return (1);
}

int	ft_update_image(t_var *var)
{
	if (var->mini_map.img_ptr && var->screen.img_ptr)
	{
		mlx_destroy_image(var->mlx_ptr, var->mini_map.img_ptr);
		mlx_destroy_image(var->mlx_ptr, var->screen.img_ptr);
		ft_init_img(var, &(var->screen));
		ft_draw_background(var, &(var->screen));
		ft_init_img(var, &(var->mini_map));
		ft_draw_minimap(var);
		ft_put_image_to_window(var, &(var->screen));
		ft_put_image_to_window(var, &(var->mini_map));
	}
	return (0);
}
