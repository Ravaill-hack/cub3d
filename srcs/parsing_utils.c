/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:12:51 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 14:26:44 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_go_to_map_first_line(int fd, char *tmp)
{
	tmp = get_next_line(fd);
	while (tmp && ft_first_char(tmp) != '1')
		tmp = ft_free_line_go_to_next_line(fd, tmp);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	ft_map_size_x(t_var *var)
{
	int		fd;
	char	*tmp;
	int		len_max;

	len_max = 0;
	fd = open(var->win.path, O_RDONLY);
	tmp = ft_go_to_map_first_line(fd, tmp);
	if (!tmp)
		return (-1);
	while (tmp && ft_line_is_empty(tmp) == 0)
	{
		if (ft_strlen(tmp) > len_max)
			len_max = ft_strlen(tmp);
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

