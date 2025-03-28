/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/28 17:11:20 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_import_xpm_img(t_var *var, char *path, t_img *img)
{
	(void)var;
	img->data_addr = mlx_xpm_file_to_image(var->mlx_ptr, path, &img->width, &img->height);
	if (!img->data_addr)
		return (NULL);
	return (img);
}

t_textures *ft_init_textures(t_var *var)
{
	if (!ft_import_xpm_img(var, var->txtr.SO_img.path, &var->txtr.SO_img))
		return (NULL);
	if (!ft_import_xpm_img(var, var->txtr.WE_img.path, &var->txtr.WE_img))
		return (NULL);
	if (!ft_import_xpm_img(var, var->txtr.EA_img.path, &var->txtr.EA_img))
		return (NULL);
	if (!ft_import_xpm_img(var, var->txtr.NO_img.path, &var->txtr.NO_img))
		return (NULL);
	return (&var->txtr);
}

int	main(int argc, char **argv)
{
	t_var	var;

	(void)argc;
	// var.status = ft_init_var(&var, argv[1]);
	// if (var.status == -1)
	// 	return (ft_exit_error("Error\n"));
	var.mlx_ptr = mlx_init();
	mlx_get_screen_size(var.mlx_ptr, &(var.win.width), &(var.win.height));
	var.win.title = ft_strdup(argv[1]);
	var.win.win_ptr = mlx_new_window(var.mlx_ptr, var.win.width, var.win.height, var.win.title);
	ft_import_xpm_img(&var, "./includes/textures/basalt_top.xpm", &(var.txtr.NO_img));
	mlx_put_image_to_window(var.mlx_ptr, var.win.win_ptr, var.txtr.NO_img.data_addr, 100, 100);
	mlx_loop(var.mlx_ptr);
	return (0);
}
