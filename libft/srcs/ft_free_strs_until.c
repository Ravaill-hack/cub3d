/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs_until.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:56:16 by juduchar          #+#    #+#             */
/*   Updated: 2025/04/16 14:31:21 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// free an array of strings until n (not included)
char	**ft_free_strs_until(char ***strs, int n)
{
	int	i;

	i = 0;
	if (!strs || !(*strs))
		return (NULL);
	if (n == -1)
	{
		while ((*strs)[i])
		{
			ft_check_and_free((void **)(&(*strs[i])));
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			ft_check_and_free((void **)(&(*strs[i])));
			i++;
		}
	}
	if (*strs)
		return ((*strs) = NULL, free(*strs), NULL);
	return (NULL);
}
