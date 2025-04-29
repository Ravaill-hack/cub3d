/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:13:04 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 14:01:33 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_to_end_fd(int fd)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	close (fd);
}

int	ft_is_text(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

int	ft_is_col(char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "F ", 2) == 0)
		return (1);
	return (0);
}

void	*ft_parse_first_lines(t_var *var, int fd, char *line)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		line = ft_free_line_go_to_next_line(fd, line);
		if (!line)
			return (ft_err_null(ERR_FILE_EMPTY));
		if (ft_is_text(line) == 1)
		{
			if (!ft_parse_textures(var, line, &i))
				return (ft_go_to_end_fd(fd), NULL);
		}
		else if (ft_is_col(line) == 1)
		{
			if (!ft_parse_colors(var, line, &i))
				return (ft_go_to_end_fd(fd), NULL);
		}
		else
			return (ft_err_null("Error\nInvalid format for map file\n"));
	}
	if (!ft_valid_txtr(var) || !ft_init_txtr(var))
		return (NULL);
	return ((void *)var);
}

void	*ft_parse(t_var *var)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	line = NULL;
	var->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!var->map)
		return (ft_err_null(ERR_MAP_ALLOC));
	var->map->title = ft_extract_title(var->win.path);
	if (!var->map->title)
		return (NULL);
	var->map->player = 0;
	fd = open(var->win.path, O_RDONLY);
	if (fd == -1)
		return (ft_err_null(ERR_MAP_OPEN));
	if (!ft_parse_first_lines(var, fd, line) || !(ft_parse_map(var, fd, line)))
	{
		ft_go_to_end_fd(fd);
		return (NULL);
	}
	close(fd);
	return ((void *)var);
}
