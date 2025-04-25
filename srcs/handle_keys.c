/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:11:30 by julien            #+#    #+#             */
/*   Updated: 2025/04/25 11:39:57 by lmatkows         ###   ########.fr       */
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
	return (0);
}

int	ft_repeat_key_events(t_var *var)
{
	int	deceleration;

	deceleration = 4;
	if (var->input.key_w)
		ft_move(var, KEY_W);

	else if (var->input.key_s)
		ft_move(var, KEY_S);
	if (var->input.key_a)
	{
		ft_rotate(var, KEY_A);
		var->need_redraw = 1;
	}
	else if (var->input.key_d)
	{
		ft_rotate(var, KEY_D);
		var->need_redraw = 1;
	}
	if (var->need_redraw)
	{
		usleep(deceleration * 10000);
		// printf("pos x = %f, pos_y = %f, or_x = %f, or_y = %f\n",
		// 	var->play.pos_x, var->play.pos_y, var->play.or_x, var->play.or_y);
		// printf("angle = %d\n", var->play.angle);
		// printf("or_x = %f\n", var->play.or_x);
		// printf("or_y = %f\n", var->play.or_y);
		ft_update_image(var);
		var->need_redraw = 0;
	}
	return (0);
}
