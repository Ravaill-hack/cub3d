/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:15:47 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/25 14:15:56 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_min(int x1, int x2)
{
	if (x1 <= x2)
		return (x1);
	return (x2);
}

int	ft_max(int x1, int x2)
{
	if (x1 > x2)
		return (x1);
	return (x2);
}
