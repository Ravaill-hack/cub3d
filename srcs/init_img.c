/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:44:20 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 18:31:38 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
