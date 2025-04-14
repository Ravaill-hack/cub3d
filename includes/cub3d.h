/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:57:45 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 11:12:41 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include "../minilibx/mlx.h"

/*
Error messages
*/

/*
Initialization errors
*/
# define ERR_INIT_MLXPTR "Error\nFailed to init mlx_ptr\n"
# define ERR_INIT_WINPTR "Error\nFailed to init win_ptr\n"
# define ERR_INIT_PATH "Error\nError while duplicating path\n"
/*
File errors
*/
# define ERR_FILE_EXISTENCE "Error\nError file does not exist\n"
# define ERR_FILE_EMPTY "Error\nError file is empty\n"
/*
Texture errors
*/
# define ERR_TEXTR_MISSING_DATA "Error\nTexture data are missing"
# define ERR_TEXTR_SYNTAX "Error\nInvalid texture syntax\n"
/*
Color errors
*/
# define ERR_COLORS_MISSING_DATA "Error\nColors data are missing"
# define ERR_COLORS_SYNTAX "Error\nInvalid color syntax\n"
/*
Map errors
*/
# define ERR_MAP_OPEN "Error\nError while opening map file\n"
# define ERR_MAP_ALLOC "Error\nMap memory allocation failed\n"
# define ERR_MAP_READ "Error\nError while reading map file\n"
# define ERR_MAP_EXISTENCE "Error\nNo map in this file"
# define ERR_MAP_SIZE "Error\nInvalid map size\n"
# define ERR_MAP_PLAYERS "Error\nThere must be only one player\n"
# define ERR_MAP_SYNTAX "Error\nInvalid character in the map\n"


typedef struct s_pix
{
	struct s_var	*var;
	int				x;
	int				y;
	int				z;
	unsigned int	col;
}	t_pix;

// typedef struct s_line
// {
// 	t_pix			pix_1;
// 	t_pix			pix_2;
// }	t_line;

typedef struct s_img
{
	struct s_var	*var;
	void			*img_ptr;
	char			*data_addr;
	char			*path;
	int				bit_per_pix;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}	t_img;

typedef struct s_textures
{
	struct s_var	*var;
	t_img			NO_img;
	t_img			SO_img;
	t_img			WE_img;
	t_img			EA_img;
	unsigned int	FL_col;
	unsigned int	CE_col;
}	t_textures;

typedef struct s_map
{
	int				size_x;
	int				size_y;
	char			*title;
	t_pix			*tab1;
	char			**tab;
	int				player;
}	t_map;

typedef struct s_win
{
	struct s_var	*var;
	void			*win_ptr;
	char			*path;
	int				width;
	int				height;
}	t_win;

typedef struct s_var
{
	void			*mlx_ptr;
	int				status;
	t_win			win;
	t_textures		txtr;
	t_map			*map;
}	t_var;

/*
Initialization (init.c)
*/
int			ft_init_var(t_var *var, char *title);
t_textures	*ft_init_textures(t_var *var);
/*
Error (error.c)
*/
int			ft_err(char *str);
void		*ft_err_null(char *str);
/*
Free (free.c)
*/

/*
Global parsing (parsing.c)
*/
void		*ft_parse_map(t_var *var);
/*
Color parsing (parsing_colors.c)
*/
int			ft_convert_color(char *str);
void		*ft_parse_colors(t_var *var, int fd, char *line);
/*
Parsing utils (parsing_utils.c)
*/
/*
Utils (utils.c)
*/

#endif