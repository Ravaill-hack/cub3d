/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:13:04 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 10:09:40 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_extract_title(char *path)
{
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	while (path[i1])
	{
		if (path[i1] == '/')
			i2 = i1;
		i1 ++;
	}
	if (path[i2 + 1] && path[i2] == '/')
		return (ft_strdup(&path[i2 + 1]));
	return (NULL);
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
	var->map->player = 0;
	var->txtr.no_img.path = NULL;
	var->txtr.so_img.path = NULL;
	var->txtr.we_img.path = NULL;
	var->txtr.ea_img.path = NULL;
	fd = open(var->win.path, O_RDONLY);
	if (fd == -1)
		return (ft_err_null(ERR_MAP_OPEN));
	if (!ft_parse_textures(var, fd, line, i)
		|| !ft_parse_colors(var, fd, line) || !ft_parse_map(var, fd, line))
		return (NULL);
	return ((void *)var);
}
