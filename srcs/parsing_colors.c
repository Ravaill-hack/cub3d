/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:09:02 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 10:09:16 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_convert_color(char *str)
{
	t_colors	col;

	col.i = 0;
	col.col_int = 0;
	while (str[col.i] && str[col.i] != ',')
		col.i++;
	if (str[col.i] == '\0')
		return (ft_err(ERR_COLORS_SYNTAX));
	str[col.i] = '\0';
	col.col_int = ft_atoi(str) * 1000000;
	str += col.i + 1;
	col.i = 0;
	while (str[col.i] && str[col.i] != ',')
		col.i++;
	if (str[col.i] == '\0')
		return (ft_err(ERR_COLORS_SYNTAX));
	str[col.i] = '\0';
	col.col_int = col.col_int + ft_atoi(str) * 1000;
	col.i = 0;
	str += col.i + 1;
	if (*str)
		col.col_int = col.col_int + ft_atoi(str);
	else
		return (ft_err(ERR_COLORS_SYNTAX));
	return (col.col_int);
}

void	*ft_parse_colors(t_var *var, int fd, char *line)
{
	int	i;

	i = 0;
	line = ft_free_line_go_to_next_line(fd, line);
	if (!line)
		return (ft_err_null(ERR_COLORS_MISSING_DATA));
	while (i < 2)
	{
		if (line[0] == 'F' && line[1] == ' ')
			var->txtr.fl_col = ft_convert_color(&line[2]);
		else if (line[0] == 'C' && line[1] == ' ')
			var->txtr.ce_col = ft_convert_color(&line[2]);
		else
			return (ft_err_null(ERR_COLORS_SYNTAX));
		if (var->txtr.fl_col == -1 || var->txtr.ce_col == -1)
			return (NULL);
		if (i + 1 == 2)
		{
			free(line);
			break ;
		}
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	return ((void *)var);
}
