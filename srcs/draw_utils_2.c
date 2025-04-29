/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:22:56 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 13:11:03 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_nodes(t_var *var)
{
	t_pix	node;

	node.y = 0;
	while (node.y <= var->map->size_y)
	{
		node.x = 0;
		while (node.x <= var->map->size_x)
		{
			ft_connect_nodes(var, &var->mini_map, node, 0x0000FF);
			node.x++;
		}
		node.y++;
	}
}

t_line	ft_build_line(t_pix p1, t_pix p2)
{
	t_line	line;

	line.pixel_1 = p1;
	line.pixel_2 = p2;
	return (line);
}
