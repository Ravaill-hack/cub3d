/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:56:40 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/15 23:20:51 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*ft_get_or_create_file_struct(int fd, t_file **files)
{
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!files[fd])
	{
		files[fd] = (t_file *) malloc(sizeof(t_file));
		if (!files[fd])
			return (NULL);
		files[fd]->fd = fd;
		files[fd]->rm = NULL;
		files[fd]->buffer[0] = '\0';
	}
	return (files[fd]);
}

static void	ft_free_file(t_file **file)
{
	if (!file || !*file)
		return ;
	if ((*file)->rm)
	{
		free((*file)->rm);
		(*file)->rm = NULL;
	}
	free(*file);
	*file = NULL;
}

static char	*ft_extract_line(char **rm)
{
	char	*nl_pos;
	char	*temp;
	char	*line;

	if (!*rm || !**rm)
		return (NULL);
	nl_pos = ft_strchr(*rm, '\n');
	if (!nl_pos)
		return (NULL);
	line = ft_strndup(*rm, nl_pos - *rm + 1);
	if (!line)
		return (NULL);
	temp = ft_strndup(nl_pos + 1, ft_strlen(nl_pos + 1));
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	free(*rm);
	*rm = temp;
	return (line);
}

static char	*ft_finalize_line(t_file **file_ptr, ssize_t bytes_read)
{
	t_file	*file;
	char	*line;

	file = *file_ptr;
	if (bytes_read < 0 || !file->rm || !*file->rm)
	{
		ft_free_file(file_ptr);
		return (NULL);
	}
	line = ft_strndup(file->rm, ft_strlen(file->rm));
	ft_free_file(file_ptr);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_file	*files[OPEN_MAX];
	t_gnl			g;

	g.f = ft_get_or_create_file_struct(fd, files);
	if (!g.f)
		return (NULL);
	g.ln = ft_extract_line(&(g.f->rm));
	if (g.ln)
		return (g.ln);
	g.br = read(fd, g.f->buffer, BUFFER_SIZE);
	while (g.br > 0)
	{
		g.f->buffer[g.br] = '\0';
		g.f->rm = ft_strnjoin(g.f->rm, g.f->buffer, ft_strlen(g.f->rm), g.br);
		if (!g.f->rm)
			return (NULL);
		g.ln = ft_extract_line(&g.f->rm);
		if (g.ln)
			return (g.ln);
		g.br = read(fd, g.f->buffer, BUFFER_SIZE);
	}
	g.ln = ft_finalize_line(&files[fd], g.br);
	if (files[fd] && !g.ln)
		ft_free_file(&files[fd]);
	return (g.ln);
}
