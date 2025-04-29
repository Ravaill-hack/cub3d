/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:31 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 09:28:10 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	*ft_init_txtr(t_var *var)
{
	var->txtr.so_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.so_img.path, &(var->txtr.so_img.width),
			&(var->txtr.so_img.height));
	var->txtr.so_img.data_addr = mlx_get_data_addr(var->txtr.so_img.img_ptr,
			&(var->txtr.so_img.bit_per_pix), &(var->txtr.so_img.line_len),
			&(var->txtr.so_img.endian));
	var->txtr.no_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.no_img.path, &(var->txtr.no_img.width),
			&(var->txtr.no_img.height));
	var->txtr.no_img.data_addr = mlx_get_data_addr(var->txtr.no_img.img_ptr,
			&(var->txtr.no_img.bit_per_pix), &(var->txtr.no_img.line_len),
			&(var->txtr.no_img.endian));
	var->txtr.we_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.we_img.path, &(var->txtr.we_img.width),
			&(var->txtr.we_img.height));
	var->txtr.we_img.data_addr = mlx_get_data_addr(var->txtr.we_img.img_ptr,
			&(var->txtr.we_img.bit_per_pix), &(var->txtr.we_img.line_len),
			&(var->txtr.we_img.endian));
	var->txtr.ea_img.img_ptr = mlx_xpm_file_to_image(var->mlx_ptr,
			var->txtr.ea_img.path, &(var->txtr.ea_img.width),
			&(var->txtr.ea_img.height));
	var->txtr.ea_img.data_addr = mlx_get_data_addr(var->txtr.ea_img.img_ptr,
			&(var->txtr.ea_img.bit_per_pix), &(var->txtr.ea_img.line_len),
			&(var->txtr.ea_img.endian));
	if (!var->txtr.so_img.img_ptr || !var->txtr.no_img.img_ptr
		|| !var->txtr.we_img.img_ptr || !var->txtr.ea_img.img_ptr
		|| !var->txtr.so_img.data_addr || !var->txtr.no_img.data_addr
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
	var->win.height *= 0.9;
	var->win.width *= 0.9;
	var->ratio_horizon = 0.4;
	var->win.path = ft_special_strdup(title);
	if (!var->win.path)
		return (ft_err(ERR_INIT_PATH));
	ft_init_plane(&(var->plane));
	var->dist_to_plane = (double)(var->win.width / 2)
		/ tan(var->plane.fov_rad / 2);
	ft_init_txtr_var(&var->txtr);
	ft_init_inputs(&var->input);
	var->zoom_mnm = 70;
	var->step = 0.2;
	var->need_redraw = 0;
	var->screen.img_ptr = NULL;
	var->mini_map.img_ptr = NULL;
	return (1);
}
