/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:34:53 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/24 10:28:58 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_err(char *str)
{
	ssize_t	ret;

	while (*str)
		ret = write (2, str++, 1);
	(void)ret;
	return (0);
}

void	*ft_err_null(char *str)
{
	ssize_t	ret;

	while (*str)
		ret = write (2, str++, 1);
	(void)ret;
	return (NULL);
}
