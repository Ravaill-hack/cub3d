/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:17:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 15:20:59 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error_texture(int wall)
{
	if (wall == 1)
		return (0);
	else
		return (ft_err("Error\nTexture not found\n"));
}

int	ft_find_texture(t_var *var, t_ray *ray, int *x, t_img **txt)
{
	if (ray->wall == 4)
	{
		*txt = &(var->txtr.ea_img);
		*x = ((var->map->size_y - ray->t_node.y) * var->zoom) % (*txt)->width;
	}
	else if (ray->wall == 2)
	{
		*txt = &(var->txtr.we_img);
		*x = (ray->t_node.y * var->zoom) % (*txt)->width;
	}
	else if (ray->wall == 5)
	{
		*txt = &(var->txtr.so_img);
		*x = ((var->map->size_x - ray->t_node.x) * var->zoom) % (*txt)->width;
	}
	else if (ray->wall == 3)
	{
		*txt = &(var->txtr.no_img);
		*x = (ray->t_node.x * var->zoom) % (*txt)->width;
	}
	else
		return (ft_error_texture(ray->wall));
	return (1);
}

int	ft_draw_column(t_var *var, t_ray *ray, t_img *img, t_line line)
{
	t_xpm_draw	xpm;

	xpm.txt = NULL;
	xpm.x_txt = 0;
	if (!ft_find_texture(var, ray, &(xpm.x_txt), &(xpm.txt)))
		return (0);
	xpm.y_txt = 0;
	xpm.i_y = 0;
	xpm.v_step = (double)xpm.txt->height / (double)ray->target_height;
	xpm.x_txt = (xpm.x_txt + xpm.txt->width) % xpm.txt->width;
	while (xpm.i_y < ray->target_height)
	{
		line.pixel_1.y ++;
		xpm.col = *((int *)(xpm.txt->data_addr + (xpm.y_txt * xpm.txt->line_len)
					+ (xpm.x_txt * xpm.txt->bit_per_pix / 8)));
		xpm.col = ft_darker_pix(xpm.col, ray->target_dist * 2);
		ft_draw_point(var, line.pixel_1, xpm.col, img);
		xpm.i_y++;
		xpm.y_txt = xpm.i_y * xpm.v_step;
	}
	return (1);
}
