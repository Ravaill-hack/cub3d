/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:59:42 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/28 21:23:23 by julien           ###   ########.fr       */
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

void	*ft_process_map_char(t_var *var, char c, int x, int y)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E' || c == ' ')
	{
		if ((c == 'N' || c == 'S' || c == 'W' || c == 'E')
			&& var->map->player == 1)
			return (var->map->tab = ft_free_strs((var->map->tab)),
				ft_err_null(ERR_MAP_PLAYERS));
		if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		{
			var->map->player = 1;
			ft_find_angle(c, var);
			ft_find_orientation(var);
			var->play.pos_x = x;
			var->play.pos_y = y;
			var->map->tab[y][x] = '0';
			return ((void *)var);
		}
		var->map->tab[y][x] = c;
	}
	else
		return (ft_err_null(ERR_MAP_SYNTAX));
	return ((void *)var);
}

void	*ft_append_map_line(t_var *var, char *ln, int y)
{
	int	x;
	int	saw_end;

	x = 0;
	saw_end = 0;
	while (x < var->map->size_x)
	{
		if (saw_end == 0 && (ln[x] == '\n' || ln[x] == '\0'))
			saw_end = 1;
		if (saw_end == 0 && ln[x] != '\0' && ln[x] != '\n')
		{
			if (!ft_process_map_char(var, ln[x], x, y))
				return (NULL);
		}
		else
			var->map->tab[y][x] = ' ';
		x++;
	}
	var->map->tab[y][x] = '\0';
	return ((void *)var);
}

void	*ft_allocate_map_tab(t_var *va)
{
	int		i;

	i = 0;
	va->map->tab = (char **)ft_calloc(va->map->size_y + 1, sizeof(char *));
	if (!va->map->tab)
		return (ft_err_null(ERR_MAP_ALLOC));
	while (i < va->map->size_y)
	{
		va->map->tab[i] = (char *)ft_calloc(va->map->size_x + 1, sizeof(char));
		if (!va->map->tab[i])
		{
			i--;
			while (i >= 0)
			{
				free(va->map->tab[i]);
				va->map->tab[i] = NULL;
				i--;
			}
			return (free(va->map->tab), va->map->tab = NULL,
				ft_err_null(ERR_MAP_ALLOC));
		}
		i++;
	}
	va->map->tab[i] = NULL;
	return ((void *)va);
}

void	*ft_parse_map(t_var *var, int fd, char *line)
{
	void	*tmp;	
	int		i;

	i = 0;
	if (!ft_is_valid_map_size(var))
		return (NULL);
	if (!ft_allocate_map_tab(var))
		return (NULL);
	line = ft_free_line_go_to_next_line(fd, line);
	if (!line)
		return (ft_err_null(ERR_MAP_EXISTENCE));
	while (line)
	{
		tmp = ft_append_map_line(var, line, i);
		if (!tmp)
			return (free(line), NULL);
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	free(line);
	if (!ft_is_valid_map(var->map, var))
		return (NULL); //renvoyer le message d'erreur dans t_map_is_valid
	return ((void *)var);
}
