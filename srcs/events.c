/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 16:58:59 by lmatkows         ###   ########.fr       */
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
		mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr, img->img_ptr, off_x, off_y);
	}
	return (0);
}

int	ft_handle_hook(int keyc, t_var *var)
{
	//printf("%d\n", keyc);
	if (keyc == 119 || keyc == 115)
	{
		ft_move(var, keyc);
		ft_update_image(var, &(var->mini_map));
	}
	if (keyc == 97 || keyc == 100)
	{
		ft_rotate(var, keyc);
		ft_update_image(var, &(var->mini_map));
	}
	if (keyc == 65307)
		ft_close_n_free(var);
	printf("pos x = %f, pos_y = %f, or_x = %f, or_y = %f\n", var->play.pos_x, var->play.pos_y, var->play.or_x, var->play.or_y);
	//printf("angle = %d\n", var->play.angle);
	//printf("or_x = %f\n", var->play.or_x);
	//printf("or_y = %f\n", var->play.or_y);
	
	return (0);
}
