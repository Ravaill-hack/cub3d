/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_angle_and_rotation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:25:59 by julien            #+#    #+#             */
/*   Updated: 2025/04/22 18:26:38 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_find_angle(char c, t_var *var)
{
	if (c == 'E')
		var->play.angle = 0;
	else if (c == 'N')
		var->play.angle = 90;
	else if (c == 'W')
		var->play.angle = 180;
	else if (c == 'S')
		var->play.angle = 270;
	return (0);
}

int	ft_find_orientation(t_var *var)
{
	var->play.or_x = cos((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	var->play.or_y = sin((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	return (0);
}
