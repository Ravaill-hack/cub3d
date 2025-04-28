/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:41:58 by julien            #+#    #+#             */
/*   Updated: 2025/04/28 21:42:07 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_build_image(t_var *var)
{
	ft_draw_nodes(var);
	ft_draw_player(var);
	ft_draw_screen(var);
	return (0);
}
