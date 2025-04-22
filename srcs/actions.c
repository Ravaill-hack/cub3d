/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:50:03 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 21:35:18 by julien           ###   ########.fr       */
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
	if (keyc == KEY_A)
	{
		printf("key A\n");
		var->play.angle = (var->play.angle - 5) % 360;
	}
	else if (keyc == KEY_D)
	{
		printf("key D\n");
		var->play.angle = (var->play.angle + 5) % 360;
	}
	else
		return (1);
	var->play.or_x = cos((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	var->play.or_y = sin((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	return (0);
}

int	ft_check_wall(double x, double y, t_map *map)
{
	if (ft_is_wall(x, y, map) == 1
		|| ft_is_wall(x + 0.25, y, map) == 1
		|| ft_is_wall(x - 0.25, y, map) == 1
		|| ft_is_wall(x, y + 0.25, map) == 1
		|| ft_is_wall(x, y - 0.25, map) == 1
		|| ft_is_wall(x + 0.25, y + 0.25, map) == 1
		|| ft_is_wall(x - 0.25, y + 0.25, map) == 1
		|| ft_is_wall(x + 0.25, y - 0.25, map) == 1
		|| ft_is_wall(x - 0.25, y - 0.25, map) == 1
	)
		return (1);
	return (0);
}

int	ft_move(t_var *var, int keyc)
{
	double	new_pos_x;
	double	new_pos_y;
	double	step;

	step = 0;
	if (keyc == KEY_W)
		step = var->step;
	else if (keyc == KEY_S)
		step = -var->step;
	else
		return (1);
	new_pos_x = var->play.pos_x + var->play.or_x * step;
	new_pos_y = var->play.pos_y + var->play.or_y * step;
	if (ft_check_wall(new_pos_x, var->play.pos_y, var->map) == 0)
	{
		var->play.pos_x = new_pos_x;
		var->need_redraw = 1;
	}
	if (ft_check_wall(var->play.pos_x, new_pos_y, var->map) == 0)
	{
		var->play.pos_y = new_pos_y;
		var->need_redraw = 1;
	}
	return (0);
}
