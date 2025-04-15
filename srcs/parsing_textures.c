/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:46:07 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/15 11:50:03 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_invalid_texture(t_var *var)
{
	(void)var;
	// A COMPLETER, NOTAMMENT RENVOYER LE MESSAGE ERREUR APPROPRIE
	return (0);
}

int	ft_check_textures(t_var *var)
{
	if (!var->txtr.NO_img.path)
		return (ft_err(ERR_TEXTR_NO_MISSING));
	if (!var->txtr.SO_img.path)
		return (ft_err(ERR_TEXTR_SO_MISSING));
	if (!var->txtr.WE_img.path)
		return (ft_err(ERR_TEXTR_WE_MISSING));
	if (!var->txtr.EA_img.path)
		return (ft_err(ERR_TEXTR_EA_MISSING));
	return (0);
}

void	*ft_parse_textures(t_var *var, int fd, char *line, int i)
{
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
			free(line);
			break;
		}
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	if (ft_check_textures(var) || ft_is_invalid_texture(var) || !ft_init_textures(var))
		return (NULL);
	return ((void *)var);
}

