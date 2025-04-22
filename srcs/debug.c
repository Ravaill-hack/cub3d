/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:35:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 13:47:41 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_parsed_data(t_var *var)
{
	ft_putstr_fd("Map title : ", 1);
	ft_putstr_fd(var->map->title, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("North img : ", 1);
	ft_putstr_fd(var->txtr.no_img.path, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("East img : ", 1);
	ft_putstr_fd(var->txtr.ea_img.path, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("South img : ", 1);
	ft_putstr_fd(var->txtr.so_img.path, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("West img : ", 1);
	ft_putstr_fd(var->txtr.we_img.path, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Floor color : ", 1);
	ft_putnbr_fd(var->txtr.fl_col, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Sky color : ", 1);
	ft_putnbr_fd(var->txtr.ce_col, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("Map size_x = ", 1);
	ft_putnbr_fd(var->map->size_x, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Map size_y = ", 1);
	ft_putnbr_fd(var->map->size_y, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Map data :\n ", 1);
	ft_print_strs(var->map->tab);
	printf("Player angle : %d\n", var->play.angle);
	printf("Player or_x : %f\n", var->play.or_x);
	printf("Player or_y : %f\n", var->play.or_y);
	mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
			var->txtr.no_img.img_ptr, 100, 100);
	mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
			var->txtr.ea_img.img_ptr, 200, 100);
	mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
			var->txtr.we_img.img_ptr, 100, 200);
	mlx_put_image_to_window(var->mlx_ptr, var->win.win_ptr,
			var->txtr.so_img.img_ptr, 200, 200);
	return (0);
}
