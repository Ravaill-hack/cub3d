/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 18:35:26 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_x_camera(t_var *var, int *ray_x, int *ray_y, int x)
{
	double	cam_x;

	cam_x = (2 * (double)x / (double)var->win.width - 1.0);
	*ray_x = var->play.or_x + var->plane.x * cam_x;
	*ray_y = var->play.or_y + var->plane.y * cam_x;
	return (0);
}

int	ft_set_plane(t_var *var)
{
	var->plane.x = -var->play.or_y * var->plane.len;
	var->plane.y = var->play.or_x * var->plane.len;
	return (0);
}

int	ft_build_screen(t_var *var)
{
	(void)var;
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		img_x;
	int		img_y;

	(void)argc;
	img_x = var.win.width - (var.map->size_x + 2) * var.zoom_mnm;
	img_y = var.win.height - (var.map->size_y + 2) * var.zoom_mnm;
	if (!(ft_init_var(&var, argv[1]) && ft_parse(&var) && ft_init_window(&var)))
		return (ft_free_all(&var));
	ft_init_img(&var, &(var.mini_map));
	ft_draw_minimap(&var);
	mlx_put_image_to_window(var.mlx_ptr, var.win.win_ptr,
		var.mini_map.img_ptr, img_x, img_y);
	//ft_print_parsed_data(&var);
	//mlx_hook(var.win.win_ptr, 17, 0, ft_close_n_free, (void *)(&var));
	mlx_hook(var.win.win_ptr, KeyPress, KeyPressMask,
		ft_handle_keypress, (void *)(&var));
	mlx_hook(var.win.win_ptr, KeyRelease, KeyReleaseMask,
		ft_handle_keyrelease, (void *)(&var));
	mlx_hook(var.win.win_ptr, DestroyNotify, StructureNotifyMask,
		ft_close_n_free, (void *)&var);
	mlx_loop(var.mlx_ptr, ft_repeat_key_events, (void *)&var);
	//mlx_key_hook(var.win.win_ptr, ft_handle_hook, (void *)(&var));
	mlx_loop(var.mlx_ptr);
	ft_free_all(&var);
	return (0);
}
