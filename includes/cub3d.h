/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:57:45 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/14 09:52:45 by lmatkows         ###   ########.fr       */
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
Map parsing (parsing.c)
*/
t_map		*ft_parse_map(t_var *var);
/*
Utils (utils.c)
*/

#endif