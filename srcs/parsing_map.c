/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:59:42 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 09:44:21 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_find_angle(char c, t_var *var)
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

int		ft_find_orientation(t_var *var)
{
	var->play.or_x = cos((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	var->play.or_y = sin((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	return (0);
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
			if (ln[x] == '0' || ln[x] == '1' || ln[x] == 'N' || ln[x] == 'S' || ln[x] == 'W' || ln[x] == 'E' || ln[x] == ' ')
			{
				if ((ln[x] == 'N' || ln[x] == 'S' || ln[x] == 'W' || ln[x] == 'E') && var->map->player == 1)
					return (ft_free_strs_until(&(var->map->tab), y),
						ft_err_null(ERR_MAP_PLAYERS));
				if (ln[x] == 'N' || ln[x] == 'S' || ln[x] == 'W' || ln[x] == 'E')
				{
					var->map->player = 1;
					ft_find_angle(ln[x], var);
					ft_find_orientation(var);
				}
				var->map->tab[y][x] = ln[x];
			}
			else
				return (ft_err_null(ERR_MAP_SYNTAX));
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
