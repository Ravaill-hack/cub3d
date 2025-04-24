/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/24 13:23:05 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_x_camera(t_var *var, int *ray_x, int *ray_y, int x)
{
	double	cam_x;

	cam_x = (2 * (double)x / (double)var->win.width - 1.0);
	*ray_x = var->play.or_x + var->plane.x * cam_x;
	*ray_y = var->play.or_y + var->plane.y * cam_x;
	return (1);
}

int	ft_set_plane(t_var *var)
{
	var->plane.x = -var->play.or_y * var->plane.len;
	var->plane.y = var->play.or_x * var->plane.len;
	return (1);
}

int	ft_put_image_to_window(t_var *var, t_img *img)
{
	mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
		img->img_ptr, img->off_x, img->off_y);
	return (1);
}

int	ft_draw_background(t_var *var, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < var->h_horizon)
	{
		x = 0;
		while (x <= var->win.width)
		{
			ft_draw_point(var, x, y, var->txtr.ce_col, img);
			x++;
		}
		y++;
	}
	while (y <= var->win.height)
	{
		x = 0;
		while (x <= var->win.width)
		{
			ft_draw_point(var, x, y, var->txtr.fl_col, img);
			x++;			
		}
		y++;
	}
	return (1);
}

int	ft_init_game_screen(t_var *var)
{
	ft_init_img(var, &var->screen);
	var->screen.off_x = 0;
	var->screen.off_y = 0;
	// test
	// ft_draw_disc(var, 400, 200, 0x00FF00, &(var->screen));
	// ft_draw_disc(var, 400, 300, 0xFFFF00, &(var->screen));
	// ft_draw_disc(var, 400, 400, 0xFF0000, &(var->screen));
	// ft_draw_disc(var, 300, 400, 0xFF00FF, &(var->screen));
	// ft_draw_disc(var, 200, 400, 0x0000FF, &(var->screen));
	// test
	/*
	ft_calculate_first_game_screen(var);
	*/
	ft_draw_background(var, &(var->screen));
	ft_put_image_to_window(var, &(var->screen));
	return (1);
}

int	ft_init_mini_map(t_var *var)
{
	ft_init_img(var, &(var->mini_map));
	var->mini_map.off_x = var->win.width - (var->map->size_x + 2) * var->zoom_mnm;
	var->mini_map.off_y = var->win.height - (var->map->size_y + 2) * var->zoom_mnm;
	ft_draw_minimap(var);
	ft_put_image_to_window(var, &(var->mini_map));
	return (1);
}

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 2)
		return (ft_err("Error\nOne argument is expected\n"));
	if (!(ft_init_var(&var, argv[1]) && ft_parse(&var) && ft_init_window(&var)))
		return (ft_free_all(&var));
	ft_init_game_screen(&var);
	ft_init_mini_map(&var);
	//ft_print_parsed_data(&var);
	mlx_hook(var.win.win_ptr, KeyPress, KeyPressMask,
		ft_handle_keypress, (void *)(&var));
	mlx_hook(var.win.win_ptr, KeyRelease, KeyReleaseMask,
		ft_handle_keyrelease, (void *)(&var));
	mlx_hook(var.win.win_ptr, DestroyNotify, StructureNotifyMask,
		ft_close_n_free, (void *)&var);
	mlx_loop_hook(var.mlx_ptr, ft_repeat_key_events, (void *)&var);
	mlx_loop(var.mlx_ptr);
	ft_free_all(&var);
	return (0);
}
