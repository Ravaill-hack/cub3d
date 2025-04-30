/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:31 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/30 09:43:00 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_window(t_var *var)
{
	var->win.win_ptr = mlx_new_window(var->mlx_ptr, var->win.width,
			var->win.height, var->win.path);
	if (!var->win.win_ptr)
		return (ft_err(ERR_INIT_WINPTR));
	return (1);
}

void	ft_init_inputs(t_input *input)
{
	input->key_w = 0;
	input->key_a = 0;
	input->key_s = 0;
	input->key_d = 0;
	input->key_lft = 0;
	input->key_rgt = 0;
}

int	ft_init_var(t_var *var, char *title)
{
	var->mlx_ptr = mlx_init();
	if (!var->mlx_ptr)
		return (ft_err(ERR_INIT_MLXPTR));
	var->win.win_ptr = NULL;
	mlx_get_screen_size(var->mlx_ptr, &(var->win.width), &(var->win.height));
	var->win.height *= 0.7;
	var->win.width *= 0.7;
	var->ratio_horizon = 0.6;
	var->win.path = ft_special_strdup(title);
	if (!var->win.path)
		return (ft_err(ERR_INIT_PATH));
	ft_init_plane(&(var->plane));
	var->dist_to_plane = (double)(var->win.width / 2)
		/ tan(var->plane.fov_rad / 2);
	ft_init_txtr_var(&var->txtr);
	ft_init_inputs(&var->input);
	var->zoom = 30;
	var->step = 0.2;
	var->need_redraw = 0;
	var->screen.img_ptr = NULL;
	var->mini_map.img_ptr = NULL;
	return (1);
}

void	ft_init_plane(t_plane *plane)
{
	plane->fov_deg = 80;
	plane->fov_rad = plane->fov_deg * 2.0 * M_PI / 360.0;
	plane->len = tan(plane->fov_rad / 2.0);
	plane->x = 0;
	plane->y = 0;
	plane->h_wall = 10;
}
