/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:50:03 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 16:30:10 by lmatkows         ###   ########.fr       */
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
	if (keyc == 97)
		var->play.angle = (var->play.angle - 5) % 360;
	else if (keyc == 100)
		var->play.angle = (var->play.angle + 5) % 360;
	else
		return (1);
	var->play.or_x = cos((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	var->play.or_y = sin((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	return (0);
}

int	ft_move(t_var *var, int keyc)
{
	if (keyc == 119)
		var->play.forw = var->step;
	else if (keyc == 115)
		var->play.forw = -var->step;
	else
		return (1);
	var->play.pos_x = var->play.pos_x + var->play.or_x * var->play.forw;
	var->play.pos_y = var->play.pos_y + var->play.or_y * var->play.forw;
	return (0);
}
