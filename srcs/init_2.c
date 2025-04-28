/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:19:41 by julien            #+#    #+#             */
/*   Updated: 2025/04/28 21:19:51 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_plane(t_plane *plane)
{
	plane->fov_deg = 80;
	plane->fov_rad = plane->fov_deg * 2.0 * M_PI / 360.0;
	plane->len = tan(plane->fov_rad / 2.0);
	plane->x = 0;
	plane->y = 0;
	plane->h_wall = 10;
}
