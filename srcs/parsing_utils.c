/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:12:51 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 11:13:49 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	ft_map_size_x(t_var *var)
{
	int		fd;
	char	*tmp;
	int		count;

	count = 0;
	tmp = get_next_line(fd);
	fd = open(var->win.path, O_RDONLY);
	while (ft_is_first_line_map(tmp) != 1)
	{
		tmp = get_next_line(fd);
		free(tmp);
	}
	while (ft_line_is_empty(fd) == 0)
	{
		tmp = get_next_line(fd);
		free(tmp);
		count ++;
	}
	return (count);
}

