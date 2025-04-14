/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:13:04 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 11:13:52 by lmatkows         ###   ########.fr       */
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

void	*ft_parse_textures(t_var *var, int fd, char *line)
{
	int		i;

	i = 0;
	line = ft_free_line_go_to_next_line(fd, line);
	if (!line)
		return (ft_err_null(ERR_FILE_EMPTY));
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
			return (ft_err_null(ERR_TEXTR_SYNTAX));
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

void	*ft_append_map_line(t_var *var, char *line, int y)
{
	int	x;

	x = 0;
	while (x < var->map->size_x)
	{
		if (line[x] != '\0')
		{
			if (line[x] == '0' || line[x] == '1' || line[x] == 'N' || line[x] == ' ')
			{
				if (line[x] == 'N' && var->map->player == 1)
					return (ft_err_null(ERR_MAP_PLAYERS)); // et free les lignes precedentes a rajouter peut etre dans le main
				if (line[x] == 'N')
					var->map->player = 1;
				var->map->tab[y][x] = line[x];
			}
			else
				return (ft_err_null(ERR_MAP_SYNTAX));
		}
		else
			var->map->tab[y][x] = ' ';
		x++;
	}
	return ((void *)var);
}

void	*ft_allocate_char_tab(t_var *var)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)ft_calloc(var->map->size_y + 1, sizeof(char *));
	if (!tab)
		return (ft_err_null(ERR_MAP_ALLOC));
	while (i < var->map->size_y)
	{
		tab[i] = (char *)ft_calloc(var->map->size_x + 1, sizeof(char));
		if (!tab[i])
			return (ft_err_null(ERR_MAP_ALLOC)); // et free les lignes precedentes a rajouter
		i++;
	}
	tab[i] = NULL;
	return ((void *)var);
}

void	*ft_store_map(t_var *var, int fd, char *line)
{
	void	*tmp;	
	int		i;

	i = 0;
	var->map->size_x = ft_map_size_x(var);
	var->map->size_y = ft_map_size_y(var);
	if (ft_is_valid_map_size(var->map->size_x, var->map->size_y) == 0)
		return (ft_err_null(ERR_MAP_SIZE));
	if (!ft_allocate_char_tab(var))
		return (ft_err_null(ERR_MAP_ALLOC));
	line = ft_go_to_next_line(fd);
	if (!line)
		return (ft_err_null(ERR_MAP_EXISTENCE));
	while (line)
	{
		tmp = ft_append_map_line(var, line, i);
		if (!tmp)
			return (ft_err_null(ERR_MAP_READ));
		free(line);
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	free(line);
	if (ft_is_valid_map(var->map, var) == 0)
		return (NULL); //renvoyer le message d'erreur approprie dans la fonction ft_map_is_valid
	return ((void *)var);
}

void	*ft_parse_map(t_var *var)
{
	char	*line;
	int		fd;
	void	*tmp;

	line = NULL;
	var->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!var->map)
		return (ft_err_null(ERR_MAP_ALLOC));
	tmp = NULL;
	var->map->title = ft_extract_title(var->win.path);
	var->map->player = 0;
	fd = open(var->win.path, O_RDONLY);
	if (fd == -1)
		return (ft_err_null(ERR_MAP_OPEN));	
	tmp = ft_parse_textures(var, fd, line);
	if (!tmp)
		return (NULL);
	tmp = ft_parse_colors(var, fd, line);
	if (!tmp)
		return (NULL);
	tmp = ft_store_map(var, fd, line);
	if (!tmp)
		return (NULL);
	return ((void *)var->map);
}
