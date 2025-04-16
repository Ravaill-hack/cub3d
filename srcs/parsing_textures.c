/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:46:07 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 10:27:34 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_invalid_txtr(t_var *var)
{
	(void)var;
	// A COMPLETER, NOTAMMENT RENVOYER LE MESSAGE ERREUR APPROPRIE
	return (0);
}

int	ft_check_txtr(t_var *var)
{
	if (!var->txtr.no_img.path)
		return (ft_err(ERR_TEXTR_NO_MISSING));
	if (!var->txtr.so_img.path)
		return (ft_err(ERR_TEXTR_SO_MISSING));
	if (!var->txtr.we_img.path)
		return (ft_err(ERR_TEXTR_WE_MISSING));
	if (!var->txtr.ea_img.path)
		return (ft_err(ERR_TEXTR_EA_MISSING));
	return (0);
}

void	*ft_parse_textures(t_var *var, int fd, char *line, int i)
{
	line = ft_free_line_go_to_next_line(fd, line);
	if (!line)
		return (ft_err_null(ERR_FILE_EMPTY));
	while (i++ < 4)
	{
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			var->txtr.no_img.path = ft_special_strdup(&line[3]);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			var->txtr.so_img.path = ft_special_strdup(&line[3]);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			var->txtr.we_img.path = ft_special_strdup(&line[3]);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			var->txtr.ea_img.path = ft_special_strdup(&line[3]);
		else
			return (ft_err_null(ERR_TEXTR_SYNTAX));
		if (i == 4)
		{
			free(line);
			break ;
		}
		line = ft_free_line_go_to_next_line(fd, line);
	}
	if (ft_check_txtr(var) || ft_invalid_txtr(var) || !ft_init_txtr(var))
		return (NULL);
	return ((void *)var);
}
