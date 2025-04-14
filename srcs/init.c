/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:31 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 10:54:37 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	*ft_init_textures(t_var *var)
{
	var->txtr.SO_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
		var->txtr.SO_img.path, &(var->txtr.SO_img.width),
		&(var->txtr.SO_img.height));
	var->txtr.NO_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
		var->txtr.NO_img.path, &(var->txtr.NO_img.width),
		&(var->txtr.NO_img.height));
	var->txtr.WE_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
		var->txtr.WE_img.path,&(var->txtr.WE_img.width),
		&(var->txtr.WE_img.height));
	var->txtr.EA_img.data_addr = mlx_xpm_file_to_image(var->mlx_ptr,
		var->txtr.EA_img.path, &(var->txtr.EA_img.width),
		&(var->txtr.EA_img.height));
	if (!var->txtr.SO_img.data_addr || !var->txtr.NO_img.data_addr
		|| !var->txtr.WE_img.data_addr || !var->txtr.EA_img.data_addr)
		return (NULL);
	return (&var->txtr);
}

int	ft_init_var(t_var *var, char *title)
{
	var->mlx_ptr = mlx_init();
	if (!var->mlx_ptr)
		return (ft_err(ERR_INIT_MLXPTR));
	mlx_get_screen_size(var->mlx_ptr, &(var->win.width), &(var->win.height));
	var->win.path = ft_strdup(title);
	if (!var->win.path)
		return (ft_err(ERR_INIT_PATH));
	var->win.win_ptr = mlx_new_window(var->mlx_ptr, var->win.width,
		var->win.height, var->win.path);
	if (!var->win.win_ptr)
		return (ft_err(ERR_INIT_WINPTR));
	return (0);
}