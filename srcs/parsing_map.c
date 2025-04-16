/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:59:42 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 14:34:48 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_append_map_line(t_var *var, char *ln, int y)
{
	int	x;

	x = 0;
	while (x < var->map->size_x)
	{
		if (ln[x] != '\0' && ln[x] != '\n')
		{
			if (ln[x] == '0' || ln[x] == '1' || ln[x] == 'N' || ln[x] == ' ')
			{
				if (ln[x] == 'N' && var->map->player == 1)
					return (ft_free_strs_until(&(var->map->tab), y),
						ft_err_null(ERR_MAP_PLAYERS));
				if (ln[x] == 'N')
					var->map->player = 1;
				var->map->tab[y][x] = ln[x];
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
			return (ft_err_null(ERR_MAP_ALLOC));
			//free les lignes precedentes a rajouter
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
	if (!ft_is_valid_map_size(var) || !ft_allocate_map_tab(var))
		return (NULL);
	line = ft_free_line_go_to_next_line(fd, line);
	if (!line)
		return (ft_err_null(ERR_MAP_EXISTENCE));
	while (line)
	{
		tmp = ft_append_map_line(var, line, i);
		if (!tmp)
			return (ft_err_null(ERR_MAP_READ));
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	free(line);
	if (ft_is_valid_map(var->map, var) == 0)
		return (NULL); //renvoyer le message d'erreur dans t_map_is_valid
	return ((void *)var);
}
