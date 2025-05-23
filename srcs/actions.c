/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:50:03 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/30 09:49:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_n_free(void *v)
{
	t_var	*var;

	var = (t_var *)v;
	ft_free_all(var);
	exit(0);
}

int	ft_rotate(t_var *var, int keyc)
{
	if (keyc == KEY_LFT)
		var->play.angle = (var->play.angle + 355) % 360;
	else if (keyc == KEY_RGT)
		var->play.angle = (var->play.angle + 5) % 360;
	else
		return (1);
	var->play.or_x = cos((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	var->play.or_y = sin((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	return (0);
}

void	ft_check_wall_collision(t_var *var, double new_pos_x, double new_pos_y)
{
	if (ft_check_wall(new_pos_x * var->zoom,
			var->play.pos_y * var->zoom, var->map, var->zoom) == 0)
	{
		var->play.pos_x = new_pos_x;
		var->need_redraw = 1;
	}
	if (ft_check_wall(var->play.pos_x * var->zoom,
			new_pos_y * var->zoom, var->map, var->zoom) == 0)
	{
		var->play.pos_y = new_pos_y;
		var->need_redraw = 1;
	}
}

int	ft_move(t_var *var, int keyc)
{
	double	new_pos_x;
	double	new_pos_y;
	double	step_frwrd;
	double	step_aside;

	step_frwrd = 0;
	step_aside = 0;
	if (keyc == KEY_W)
		step_frwrd = var->step;
	else if (keyc == KEY_S)
		step_frwrd = -var->step;
	else if (keyc == KEY_A)
		step_aside = var->step;
	else if (keyc == KEY_D)
		step_aside = -var->step;
	else
		return (1);
	new_pos_x = var->play.pos_x + var->play.or_x * step_frwrd
		+ var->play.or_y * step_aside;
	new_pos_y = var->play.pos_y + var->play.or_y * step_frwrd
		- var->play.or_x * step_aside;
	ft_check_wall_collision(var, new_pos_x, new_pos_y);
	return (0);
}

int	ft_build_image(t_var *var)
{
	ft_draw_nodes(var);
	ft_draw_player(var);
	ft_draw_screen(var);
	return (0);
}
