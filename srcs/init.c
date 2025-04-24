/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:31 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/24 10:58:47 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	*ft_init_txtr(t_var *var)
{
	var->txtr.so_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.so_img.path, &(var->txtr.so_img.width),
			&(var->txtr.so_img.height));
	var->txtr.no_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.no_img.path, &(var->txtr.no_img.width),
			&(var->txtr.no_img.height));
	var->txtr.we_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.we_img.path, &(var->txtr.we_img.width),
			&(var->txtr.we_img.height));
	var->txtr.ea_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.ea_img.path, &(var->txtr.ea_img.width),
			&(var->txtr.ea_img.height));
	if (!var->txtr.so_img.img_ptr || !var->txtr.no_img.img_ptr
		|| !var->txtr.we_img.img_ptr || !var->txtr.ea_img.img_ptr)
		return (ft_err_null(ERR_TEXTR_PATH));
	return (&var->txtr);
}

int	ft_init_window(t_var *var)
{
	var->win.win_ptr = mlx_new_window(var->mlx_ptr, var->win.width,
			var->win.height, var->win.path);
	if (!var->win.win_ptr)
		return (ft_err(ERR_INIT_WINPTR));
	return (1);
}

void	ft_init_txtr_var(t_textures *txtr)
{
	txtr->no_img.img_ptr = NULL;
	txtr->so_img.img_ptr = NULL;
	txtr->we_img.img_ptr = NULL;
	txtr->ea_img.img_ptr = NULL;
	txtr->no_img.path = NULL;
	txtr->so_img.path = NULL;
	txtr->we_img.path = NULL;
	txtr->ea_img.path = NULL;
	txtr->fl_col = 0;
	txtr->ce_col = 0;
}

int	ft_init_var(t_var *var, char *title)
{
	var->mlx_ptr = mlx_init();
	if (!var->mlx_ptr)
		return (ft_err(ERR_INIT_MLXPTR));
	var->win.win_ptr = NULL;
	mlx_get_screen_size(var->mlx_ptr, &(var->win.width), &(var->win.height));
	var->win.height *= 0.9;
	var->win.width *= 0.9;
	var->win.path = ft_special_strdup(title);
	if (!var->win.path)
		return (ft_err(ERR_INIT_PATH));
	var->plane.fov_deg = 80;
	var->plane.fov_rad = var->plane.fov_deg * 2.0 * M_PI / 360.0;
	var->plane.len = tan(var->plane.fov_rad / 2.0);
	var->plane.x = 0;
	var->plane.y = 0;
	var->plane.h_wall = 10;
	ft_init_txtr_var(&var->txtr);
	var->zoom_mnm = 30;
	var->step = 0.2;
	var->input.key_w = 0;
	var->input.key_a = 0;
	var->input.key_s = 0;
	var->input.key_d = 0;
	var->need_redraw = 0;
	var->mini_map.img_ptr = NULL;
	var->screen.img_ptr = NULL;
	return (1);
}
