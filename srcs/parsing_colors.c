/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:09:02 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 15:26:26 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_convert_color(char *str)
{
	t_colors	col;

	col.i = 0;
	while (str[col.i] && str[col.i] != ',')
		col.i++;
	if (str[col.i] == '\0')
		return (ft_err(ERR_COLORS_SYNTAX));
	str[col.i] = '\0';
	col.r = ft_atoi(str);
	str += col.i + 1;
	col.i = 0;
	while (str[col.i] && str[col.i] != ',')
		col.i++;
	if (str[col.i] == '\0')
		return (ft_err(ERR_COLORS_SYNTAX));
	str[col.i] = '\0';
	col.v = ft_atoi(str);
	str += col.i + 1;
	col.b = ft_atoi(str);
	return ((col.r << 16) | (col.v << 8) | col.b);
}

void	*ft_parse_colors(t_var *var, char *line, int *i)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		var->txtr.fl_col = ft_convert_color(&line[2]);
		if (var->txtr.fl_col == -1)
			return (NULL);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		var->txtr.ce_col = ft_convert_color(&line[2]);
		if (var->txtr.ce_col == -1)
			return (NULL);
	}
	(*i)++;
	return ((void *)var);
}

int	ft_darker_pix(int col, int dist)
{
	t_colors	color;
	int			reduc;

	reduc = dist / 4.0;
	color.r = (col & 0xFF0000) >> 16;
	color.v = (col & 0x00FF00) >> 8;
	color.b = (col & 0x0000FF);
	if (color.r - reduc >= 0)
		color.r -= reduc;
	else
		color.r = 0;
	if (color.v - reduc >= 0)
		color.v -= reduc;
	else
		color.v = 0;
	if (color.b - reduc >= 0)
		color.b -= reduc;
	else
		color.b = 0;
	return ((color.r << 16) | (color.v << 8) | color.b);
}
