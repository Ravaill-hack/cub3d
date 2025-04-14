/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:09:02 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 11:10:31 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_convert_color(char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == '\0')
		return (ft_err(ERR_COLORS_SYNTAX));
	str[i] = '\0';
	res = ft_atoi(str) * 1000000;
	str += i + 1;
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == '\0')
		return (ft_err(ERR_COLORS_SYNTAX));
	str[i] = '\0';
	res = res + ft_atoi(str) * 1000;
	str += i + 1;
	if (*str)
		res = res + ft_atoi(str);
	else
		return (ft_err(ERR_COLORS_SYNTAX));
	return (res);
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
			var->txtr.FL_col = ft_convert_color(&line[2]);
		else if (line[0] == 'C' && line[1] == ' ')
			var->txtr.CE_col = ft_convert_color(&line[2]);
		else
			return (ft_err_null(ERR_COLORS_SYNTAX));
		if (var->txtr.FL_col == -1 || var->txtr.CE_col == -1)
			return (NULL);
		if (i + 1 == 2)
		{
			free(line);
			break;
		}
		line = ft_free_line_go_to_next_line(fd, line);
		i++;
	}
	return ((void *)var);
}
