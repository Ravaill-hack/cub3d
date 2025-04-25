/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:13:04 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/25 14:18:40 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_to_end_fd(int fd)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	close (fd);
}

void	*ft_parse(t_var *var)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	line = NULL;
	var->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!var->map)
		return (ft_err_null(ERR_MAP_ALLOC));
	var->map->title = ft_extract_title(var->win.path);
	if (!var->map->title)
		return (NULL);
	var->map->player = 0;
	fd = open(var->win.path, O_RDONLY);
	if (fd == -1)
		return (ft_err_null(ERR_MAP_OPEN));
	if (!(ft_parse_textures(var, fd, line, i) && ft_parse_colors(var, fd, line)
			&& ft_parse_map(var, fd, line)))
	{
		ft_go_to_end_fd(fd);
		return (NULL);
	}
	close(fd);
	return ((void *)var);
}
