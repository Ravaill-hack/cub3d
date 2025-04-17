/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:58:37 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/17 11:01:13 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// compare two strings

// DESCRIPTION :
// The ft_strcmp() function compares the two strings s1 and s2

// The comparison is done using unsigned characters
// ft_strncmp() returns an integer indicating
// the result of the comparison, as follows:
// 0, if the s1 and s2 are equal
// a negative value if s1 is less than s2
// a positive value if s1 is greater than s2

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
