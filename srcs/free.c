/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:02 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 18:33:26 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_free_win(t_var *var)
{
	if (var->win.path)
		ft_check_and_free((void **)(&var->win.path));
	if (var->mlx_ptr && var->win.win_ptr)
		mlx_destroy_window(var->mlx_ptr, var->win.win_ptr);
	if (var->mlx_ptr)
		mlx_destroy_display(var->mlx_ptr);
	return (1);
}

int	ft_free_txtr(t_var *var)
{
	ft_check_and_free((void **)(&(var->txtr.no_img.path)));
	ft_check_and_free((void **)(&(var->txtr.so_img.path)));
	ft_check_and_free((void **)(&(var->txtr.we_img.path)));
	ft_check_and_free((void **)(&(var->txtr.ea_img.path)));
	if (var->txtr.no_img.data_addr)
		mlx_destroy_image(var->mlx_ptr, var->txtr.no_img.data_addr);
	if (var->txtr.so_img.data_addr)
		mlx_destroy_image(var->mlx_ptr, var->txtr.so_img.data_addr);
	if (var->txtr.we_img.data_addr)
		mlx_destroy_image(var->mlx_ptr, var->txtr.we_img.data_addr);
	if (var->txtr.ea_img.data_addr)
		mlx_destroy_image(var->mlx_ptr, var->txtr.ea_img.data_addr);
	return (1);
}

int	ft_free_map(t_var *var)
{
	if (var->map)
	{
		if (var->map->tab)
			var->map->tab = ft_free_strs(var->map->tab);
		ft_check_and_free((void **)(&var->map->title));
		ft_check_and_free((void **)(&var->map));
	}
	return (1);
}

int	ft_free_all(t_var *var)
{
	ft_free_map(var);
	ft_free_txtr(var);
	ft_free_win(var);
	ft_check_and_free((void **)(&var->mlx_ptr));
	return (1);
}
