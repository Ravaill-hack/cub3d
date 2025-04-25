/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:12:51 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/25 14:18:44 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_map_size_x(t_var *var)
{
	int		fd;
	char	*tmp;
	size_t	len_max;

	len_max = 0;
	fd = open(var->win.path, O_RDONLY);
	tmp = NULL;
	tmp = ft_go_to_map_first_line(fd, tmp);
	if (!tmp)
		return (-1);
	while (tmp && ft_line_is_empty(tmp) == 0)
	{
		if (ft_strlen(tmp) > len_max)
			len_max = ft_strlen(tmp) - 1;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (len_max);
}

int	ft_map_size_y(t_var *var)
{
	int		fd;
	char	*tmp;
	int		count;

	count = 0;
	fd = open(var->win.path, O_RDONLY);
	tmp = NULL;
	tmp = ft_go_to_map_first_line(fd, tmp);
	if (!tmp)
		return (-1);
	while (tmp && ft_line_is_empty(tmp) == 0)
	{
		count ++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	ft_is_valid_map_size(t_var *var)
{
	var->map->size_x = ft_map_size_x(var);
	var->map->size_y = ft_map_size_y(var);
	if (var->map->size_x <= 0 || var->map->size_y <= 0)
	{
		ft_putstr_fd("Error\n", 2);
		if (var->map->size_x <= 0)
			ft_putstr_fd("Invalid map size in x\n", 2);
		if (var->map->size_y <= 0)
			ft_putstr_fd("Invalid map size in y\n", 2);
		return (0);
	}
	return (1);
}

int	ft_find_angle(char c, t_var *var)
{
	if (c == 'E')
		var->play.angle = 0;
	else if (c == 'N')
		var->play.angle = 90;
	else if (c == 'W')
		var->play.angle = 180;
	else if (c == 'S')
		var->play.angle = 270;
	return (0);
}

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
		i1++;
	}
	if (i1 < 4 || strcmp(&path[i1 - 4], ".cub") != 0)
		return (ft_err_null(ERR_MAP_FILE));
	if (path[i2 + 1] && path[i2] == '/')
		return (ft_strdup(&path[i2 + 1]));
	return (ft_strdup(path));
}
