/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:13:04 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/03 15:30:28 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_convert_color(char *str)
{
	
}

char	*ft_go_to_next_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n' && line[1] == '\0')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
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
		i1 ++;
	}
	if (path[i2 + 1] && path[i2] == '/')
		return (ft_strdup(&path[i2 + 1]));
	return (NULL);
}

void	*ft_parse_textures(t_var *var, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_go_to_next_line(fd);
	if (!line)
		return (ft_err_null("Error\nEmpty file"));
	while (i < 4)
	{
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			var->txtr.NO_img.path = ft_strdup(&line[3]);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			var->txtr.SO_img.path = ft_strdup(&line[3]);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			var->txtr.WE_img.path = ft_strdup(&line[3]);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			var->txtr.EA_img.path = ft_strdup(&line[3]);
		else
			return (ft_err_null("Error\nInvalid texture syntax\n"));
		free(line);
		if (i + 1 == 4)
			break;
		line = ft_go_to_next_line(fd);
		i++;
	}
	return ((void *)var);
}

void	*ft_parse_colors(t_var *var, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_go_to_next_line(fd);
	if (!line)
		return (ft_err_null("Error\nColors data are missing"));
	while (i < 2)
	{
		if (line[0] == 'F' && line[1] == ' ')
			var->txtr.FL_col = ft_convert_color(&line[2]);
		else if (line[0] == 'C' && line[1] == ' ')
			var->txtr.CE_col = ft_convert_color(&line[2]);
		else
			return (ft_err_null("Error\nInvalid color syntax\n"));
		if (var->txtr.FL_col == -1 || var->txtr.CE_col == -1)
			return (NULL);
		free(line);
		if (i + 1 == 2)
			break;
		line = ft_go_to_next_line(fd);
		i++;
	}
	return ((void *)var);
}

void	*ft_store_map(t_var *var, int fd)
{
	char	*line;
	void	*tmp;
	int		i;

	line = ft_go_to_next_line(fd);
	i = 0;
	if (!line)
		return (ft_err_null("Error\nNo map in this file"));
	while (line)
	{
		tmp = ft_append_map_line(var, line, i);
		if (!tmp)
			return (ft_err_null("Error\nError while reading map file\n"));
		free (line);
		line = ft_go_to_next_line(fd);
		i++;
	}
	free(line);
	return ((void *)var);
}

t_map	*ft_parse_map(t_var *var)
{
	t_map	*map;
	char	*line;
	int		fd;
	void	*tmp;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (ft_err_null("Error\nMap memory allocation failed\n"));
	tmp = NULL;
	map->title = ft_extract_title(var->win.path);
	fd = open(var->win.path, O_RDONLY);
	if (fd == -1)
		return (ft_err_null("Error\nError while opening map file\n"));	
	tmp = ft_parse_textures(var, fd);
	if (!tmp)
		return (NULL);
	tmp = ft_parse_colors(var, fd);
	if (!tmp)
		return (NULL);
	tmp = ft_store_map(var, fd);
	if (!tmp)
		return (NULL);
	return (map);
}
