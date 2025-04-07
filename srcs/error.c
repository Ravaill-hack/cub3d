/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:34:53 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/03 14:44:42 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_err(char *str)
{
	while (*str)
		write (2, str++, 1);
	return (1);
}

void	*ft_err_null(char *str)
{
	while (*str)
		write (2, str++, 1);
	return (NULL);
}
