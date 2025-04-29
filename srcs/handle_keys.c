/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:11:30 by julien            #+#    #+#             */
/*   Updated: 2025/04/29 13:20:22 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_handle_keypress(int keycode, t_var *var)
{
	if (keycode == KEY_W)
		var->input.key_w = 1;
	if (keycode == KEY_A)
		var->input.key_a = 1;
	if (keycode == KEY_S)
		var->input.key_s = 1;
	if (keycode == KEY_D)
		var->input.key_d = 1;
	if (keycode == KEY_LFT)
		var->input.key_lft = 1;
	if (keycode == KEY_RGT)
		var->input.key_rgt = 1;
	if (keycode == KEY_ESC)
		ft_close_n_free(var);
	return (0);
}

int	ft_handle_keyrelease(int keycode, t_var *var)
{
	if (keycode == KEY_W)
		var->input.key_w = 0;
	if (keycode == KEY_A)
		var->input.key_a = 0;
	if (keycode == KEY_S)
		var->input.key_s = 0;
	if (keycode == KEY_D)
		var->input.key_d = 0;
	if (keycode == KEY_LFT)
		var->input.key_lft = 0;
	if (keycode == KEY_RGT)
		var->input.key_rgt = 0;
	return (0);
}

void	ft_handle_key_move(t_var *var, t_input input)
{
	if (input.key_w)
		ft_move(var, KEY_W);
	else if (input.key_s)
		ft_move(var, KEY_S);
	else if (input.key_a)
		ft_move(var, KEY_A);
	else if (input.key_d)
		ft_move(var, KEY_D);
}

int	ft_repeat_key_events(t_var *var)
{
	ft_handle_key_move(var, var->input);
	if (var->input.key_lft)
	{
		ft_rotate(var, KEY_LFT);
		var->need_redraw = 1;
	}
	else if (var->input.key_rgt)
	{
		ft_rotate(var, KEY_RGT);
		var->need_redraw = 1;
	}
	if (var->need_redraw)
	{
		ft_update_image(var);
		var->need_redraw = 0;
	}
	return (0);
}
