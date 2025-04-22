/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:41 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 17:00:03 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_line_is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line ++;
	}
	return (1);
}

char	*ft_free_line_go_to_next_line(int fd, char *line)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	while (line && ((line[0] == '\n' && line[1] == '\0') || line[0] == '\0'))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char	ft_first_char(char *str)
{
	while (*str == ' ')
		str++;
	return (*str);
}

char	*ft_special_strdup(char *str)
{
	char	*res;

	res = ft_strdup(str);
	if (ft_strlen(res) >= 1 && res[ft_strlen(res) - 1] == '\n')
		res[ft_strlen(res) - 1] = '\0';
	return (res);
}

int	ft_is_wall(int x, int y, t_map *map)
{
	if (x < map->size_x && y < map->size_y && map->tab[y][x] == '1')
		return (1);
	return(0);
}

double	ft_deg_to_rad(int angle_deg)
{
	return ((double)angle_deg * 2.0 * M_PI / 360.0);
}

int	ft_min(int x1, int x2)
{
	if (x1 <= x2)
		return (x1);
	return (x2);
}

int	ft_max(int x1, int x2)
{
	if (x1 > x2)
		return (x1);
	return (x2);
}

double ft_distance(t_pix p1, t_pix p2)
{
	double	dist;
	int	delta_x;
	int	delta_y;

	delta_x = ft_max(p1.x, p2.x) - ft_min(p1.x, p2.x);
	delta_y = ft_max(p1.y, p2.y) - ft_min(p1.y, p2.y);
	dist = sqrtf(pow((double)delta_y, 2.0) + pow((double)delta_x, 2.0));
	return (dist);
}
