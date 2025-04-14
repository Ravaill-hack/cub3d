/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:13:04 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/10 13:47:55 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_convert_color(char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == '\0')
		return (ft_err("Error:\nMap file: invalid syntax for colors"));
	str[i] = '\0';
	res = ft_atoi(str) * 1000000;
	str += i + 1;
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == '\0')
		return (ft_err("Error:\nMap file: invalid syntax for colors"));
	str[i] = '\0';
	res = res + ft_atoi(str) * 1000;
	str += i + 1;
	if (*str)
		res = res + ft_atoi(str);
	else
		return (ft_err("Error:\nMap file: invalid syntax for colors"));
	return (res);
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

void	*ft_parse_textures(t_var *var, int fd, char *line)
{
	int		i;

	i = 0;
	line = ft_free_line_go_to_next_line(fd, line);
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
		if (i + 1 == 4)
		{
			break;
			free(line);
		}
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	return ((void *)var);
}

void	*ft_parse_colors(t_var *var, int fd, char *line)
{
	int		i;

	i = 0;
	line = ft_free_line_go_to_next_line(fd, line);
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
		{
			free(line);
			break;
		}
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	return ((void *)var);
}

void	*ft_append_map_line(t_var *var, char *line, int y)
{
	int	x;

	x = 0;
	while (x < var->map->size_x)
	{
		if (line[x] != '\0')
		{
			if (line[x] == ' ')
				var->map->tab[y][x] = -1;
			else if (line[x] == '1')
				var->map->tab[y][x] = 1;
			else if (line[x] == 'N')
				var->map->tab[y][x] = 2;
			else if (line[x] == '0')
				var->map->tab[y][x] = 0;
			else
				return (ft_err_null("Error\nInvalid character in the map\n"));
		}
		else
			var->map->tab[y][x] = -1;
		x++;
	}
	return ((void *)var);
}


void	*ft_allocate_int_tab(t_var *var)
{
	int		**tab;
	int		i;

	i = 0;
	tab = (int **)ft_calloc(var->map->size_y + 1, sizeof(int *));
	if (!tab)
		return (NULL);
	while (i < var->map->size_y)
	{
		tab[i] = (int *)ft_calloc(var->map->size_x + 1, sizeof(int));
		if (!tab[i])
			return (NULL);
		i++;
	}
	tab[i] = NULL;
	return ((void *)var);
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

void	*ft_store_map(t_var *var, int fd, char *line)
{
	void	*tmp;	
	int		i;

	i = 0;
	var->map->size_x = ft_map_size_x(var);
	var->map->size_y = ft_map_size_y(var);
	if (ft_is_valid_map_size(var->map->size_x, var->map->size_y) == 0)
		return (ft_err_null("Error\nInvalid map size\n"));
	if (!ft_allocate_int_tab(var))
		return (ft_err_null("Error\nMap memory allocation failed\n"));
	line = ft_go_to_next_line(fd);
	if (!line)
		return (ft_err_null("Error\nNo map in this file"));
	while (line)
	{
		tmp = ft_append_map_line(var, line, i);
		if (!tmp)
			return (ft_err_null("Error\nError while reading map file\n"));
		free(line);
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	free(line);
	if (ft_is_valid_map(var->map, var) == 0)
		return (NULL); //renvoyer le message d'erreur approprie dans la fonction ft_map_is_valid
	return ((void *)var);
}

t_map	*ft_parse_map(t_var *var)
{
	t_map	*map;
	char	*line;
	int		fd;
	void	*tmp;

	line = NULL;
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (ft_err_null("Error\nMap memory allocation failed\n"));
	tmp = NULL;
	map->title = ft_extract_title(var->win.path);
	fd = open(var->win.path, O_RDONLY);
	if (fd == -1)
		return (ft_err_null("Error\nError while opening map file\n"));	
	tmp = ft_parse_textures(var, fd, line);
	if (!tmp)
		return (NULL);
	tmp = ft_parse_colors(var, fd, line);
	if (!tmp)
		return (NULL);
	tmp = ft_store_map(var, fd, line);
	if (!tmp)
		return (NULL);
	return (map);
}
