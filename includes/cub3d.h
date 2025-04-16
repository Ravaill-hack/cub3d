/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:57:45 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 14:09:23 by lmatkows         ###   ########.fr       */
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
ERROR MESSAGES :

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
# define ERR_TEXTR_NO_MISSING "Error\nNorth texture is missing\n"
# define ERR_TEXTR_SO_MISSING "Error\nSouth texture is missing\n"
# define ERR_TEXTR_WE_MISSING "Error\nWest texture is missing\n"
# define ERR_TEXTR_EA_MISSING "Error\nEast texture is missing\n"
# define ERR_TEXTR_SYNTAX "Error\nInvalid texture syntax\n"
/*
Color errors
*/
# define ERR_COLORS_MISSING_DATA "Error\nColors data are missing"
# define ERR_COLORS_SYNTAX "Error\nInvalid color syntax\n"
/*
Map errors
*/
# define ERR_MAP_FILE "Error\nInvalid map file\n"
# define ERR_MAP_OPEN "Error\nCould not open map file\n"
# define ERR_MAP_ALLOC "Error\nMap memory allocation failed\n"
# define ERR_MAP_READ "Error\nError while reading map file\n"
# define ERR_MAP_EXISTENCE "Error\nNo map in this file"
# define ERR_MAP_SIZE "Error\nInvalid map size\n"
# define ERR_MAP_PLAYERS "Error\nThere must be only one player\n"
# define ERR_MAP_SYNTAX "Error\nInvalid character in the map\n"

// typedef struct s_pix
// {
// 	struct s_var	*var;
// 	int				x;
// 	int				y;
// 	int				z;
// 	unsigned int	col;
// }	t_pix;

// typedef struct s_line
// {
// 	t_pix			pix_1;
// 	t_pix			pix_2;
// }	t_line;

typedef struct s_colors
{
	int				col_int;
	int				i;
}	t_colors;

typedef struct s_img
{
	struct s_var	*var; //peut etre pas necessaire
	void			*img_ptr; //on s'en sert pas j'ail l'impression
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
	struct s_var	*var; //peut etre pas necessaire
	t_img			no_img;
	t_img			so_img;
	t_img			we_img;
	t_img			ea_img;
	int				fl_col;
	int				ce_col;
}	t_textures;

typedef struct s_map
{
	int				size_x;
	int				size_y;
	char			*title;
	// t_pix		*tab1; a supprimer
	char			**tab;
	int				player;
}	t_map;

typedef struct s_win
{
	struct s_var	*var; //peut etre pas necessaire
	void			*win_ptr;
	char			*path;
	int				width;
	int				height;
}	t_win;

typedef struct s_var
{
	void			*mlx_ptr;
	int				status; //a supprimer
	t_win			win;
	t_textures		txtr;
	t_map			*map;
}	t_var;

/*
Initialization (init.c)
*/
int			ft_init_var(t_var *var, char *title);
t_textures	*ft_init_txtr(t_var *var);
/*
Error (error.c)
*/
int			ft_err(char *str);
void		*ft_err_null(char *str);
/*
Parsing (parsing.c)
*/
char		*ft_extract_title(char *path);
void		*ft_parse(t_var *var);
/*
Map parsing (parsing_map.c)
*/
void		*ft_append_map_line(t_var *var, char *ln, int y);
void		*ft_allocate_map_tab(t_var *va);
void		*ft_parse_map(t_var *var, int fd, char *line);
/*
Color parsing (parsing_colors.c)
*/
int			ft_convert_color(char *str);
void		*ft_parse_colors(t_var *var, int fd, char *line);
/*
Parsing textures (parsing_textures.c)
*/
int			ft_check_txtr(t_var *var);
int			ft_invalid_txtr(t_var *var);
void		*ft_parse_textures(t_var *var, int fd, char *line, int i);
/*
Parsing utils (parsing_utils.c)
*/

char		*ft_go_to_map_first_line(int fd, char *tmp);
int			ft_map_size_x(t_var *var);
int			ft_map_size_y(t_var *var);
int			ft_is_valid_map_size(t_var *var);
/*
Map checker (map_checker.c)
*/
int			ft_is_valid_map(t_map *map, t_var *var);
/*
Utils (utils.c)
*/
char		*ft_free_line_go_to_next_line(int fd, char *line);
char		ft_first_char(char *str);
int			ft_line_is_empty(char *line);
char		*ft_special_strdup(char *str);
/*
Free (free.c)
*/
int			ft_free_win(t_var *var);
int			ft_free_txtr(t_var *var);
int			ft_free_map(t_var *var);
int			ft_free_all(t_var *var);
/*
Debug (debug.c)
*/
int			ft_print_parsed_data(t_var *var);

#endif