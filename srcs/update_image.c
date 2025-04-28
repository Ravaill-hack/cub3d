/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/28 21:31:06 by julien           ###   ########.fr       */
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
		ft_init_background(var);
		ft_init_img(var, &(var->mini_map));
		ft_build_image(var);
		ft_put_image_to_window(var, &(var->screen));
		ft_put_image_to_window(var, &(var->mini_map));
	}
	return (0);
}
