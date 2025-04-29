/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:46:07 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 15:26:11 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_xpm(char *str)
{
	if (!str)
	{
		ft_putstr_fd("Error\nInvalid texture file\n", 2);
		return (0);
	}
	if (ft_strlen(str) <= 4)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" is not a .xpm file\n", 2);
		return (0);
	}
	if (ft_strcmp(&str[ft_strlen(str) - 4], ".xpm") == 0)
		return (1);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" is not a .xpm file\n", 2);
	return (0);
}

int	ft_valid_txtr(t_var *var)
{
	if (ft_is_xpm(var->txtr.no_img.path) == 0
		|| ft_is_xpm(var->txtr.so_img.path) == 0
		|| ft_is_xpm(var->txtr.we_img.path) == 0
		|| ft_is_xpm(var->txtr.ea_img.path) == 0)
		return (0);
	return (1);
}

void	*ft_parse_textures(t_var *var, char *line, int *i)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		var->txtr.no_img.path = ft_special_strdup(&line[3]);
		if (!var->txtr.no_img.path)
			return (ft_err_null(ERR_TEXTR_NO_MISSING));
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		var->txtr.so_img.path = ft_special_strdup(&line[3]);
		if (!var->txtr.so_img.path)
			return (ft_err_null(ERR_TEXTR_SO_MISSING));
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		var->txtr.we_img.path = ft_special_strdup(&line[3]);
		if (!var->txtr.we_img.path)
			return (ft_err_null(ERR_TEXTR_WE_MISSING));
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		var->txtr.ea_img.path = ft_special_strdup(&line[3]);
		if (!var->txtr.ea_img.path)
			return (ft_err_null(ERR_TEXTR_EA_MISSING));
	}
	return ((*i)++, (void *)var);
}
