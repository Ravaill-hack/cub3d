/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:34:53 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 14:20:10 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_err(char *str)
{
	while (*str)
		write (2, str++, 1);
	return (0);
}

void	*ft_err_null(char *str)
{
	while (*str)
		write (2, str++, 1);
	return (NULL);
}
