/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:31 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 17:56:04 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	*ft_init_txtr(t_var *var)
{
	var->txtr.so_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.so_img.path, &(var->txtr.so_img.width),
			&(var->txtr.so_img.height));
	var->txtr.no_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.no_img.path, &(var->txtr.no_img.width),
			&(var->txtr.no_img.height));
	var->txtr.we_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.we_img.path, &(var->txtr.we_img.width),
			&(var->txtr.we_img.height));
	var->txtr.ea_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.ea_img.path, &(var->txtr.ea_img.width),
			&(var->txtr.ea_img.height));
	if (!var->txtr.so_img.data_addr || !var->txtr.no_img.data_addr
		|| !var->txtr.we_img.data_addr || !var->txtr.ea_img.data_addr)
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
		
int	ft_init_var(t_var *var, char *title)
{
	var->mlx_ptr = mlx_init();
	var->win.win_ptr = NULL;
	if (!var->mlx_ptr)
		return (ft_err(ERR_INIT_MLXPTR));
	mlx_get_screen_size(var->mlx_ptr, &(var->win.width), &(var->win.height));
	var->win.path = ft_special_strdup(title);
	if (!var->win.path)
		return (ft_err(ERR_INIT_PATH));
	var->txtr.no_img.data_addr = NULL;
	var->txtr.so_img.data_addr = NULL;
	var->txtr.we_img.data_addr = NULL;
	var->txtr.ea_img.data_addr = NULL;
	var->txtr.no_img.path = NULL;
	var->txtr.so_img.path = NULL;
	var->txtr.we_img.path = NULL;
	var->txtr.ea_img.path = NULL;
	var->txtr.fl_col = 0;
	var->txtr.ce_col = 0;
	return (1);
}
