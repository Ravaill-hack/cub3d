/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:41 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/15 10:48:12 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_line_is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line ++;
	}
	return (1);
}

char	*ft_free_line_go_to_next_line(int fd, char *line)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	while (line && ((line[0] == '\n' && line[1] == '\0') || line[0] == '\0'))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char	ft_first_char(char *str)
{
	while (*str == ' ')
		str++;
	return (*str);
}
