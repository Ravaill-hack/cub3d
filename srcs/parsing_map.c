/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:59:42 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/15 11:39:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_append_map_line(t_var *var, char *line, int y)
{
	int	x;

	x = 0;
	while (x < var->map->size_x)
	{
		if (line[x] != '\0' && line[x] != '\n')
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

void	*ft_allocate_map_tab(t_var *var)
{
	int		i;

	i = 0;
	var->map->tab = (char **)ft_calloc(var->map->size_y + 1, sizeof(char *));
	if (!var->map->tab)
		return (ft_err_null(ERR_MAP_ALLOC));
	while (i < var->map->size_y)
	{
		var->map->tab[i] = (char *)ft_calloc(var->map->size_x + 1, sizeof(char));
		if (!var->map->tab[i])
			return (ft_err_null(ERR_MAP_ALLOC)); // et free les lignes precedentes a rajouter
		i++;
	}
	var->map->tab[i] = NULL;
	return ((void *)var);
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
		return (NULL); //renvoyer le message d'erreur approprie dans la fonction ft_map_is_valid
	return ((void *)var);
}
