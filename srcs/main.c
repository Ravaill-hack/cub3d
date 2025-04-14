/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 11:08:03 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_var	var;

	(void)argc;
	var.status = ft_init_var(&var, argv[1]);
	if (var.status == 1 || !ft_parse_map(&var))
		return (1);
	//ft_import_xpm_img(&var, "./includes/textures/basalt_top.xpm", &(var.txtr.NO_img));
	mlx_put_image_to_window(var.mlx_ptr, var.win.win_ptr, var.txtr.NO_img.data_addr, 100, 100);
	mlx_loop(var.mlx_ptr);
	return (0);
}
