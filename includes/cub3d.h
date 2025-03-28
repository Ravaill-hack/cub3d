/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:57:45 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/28 17:07:32 by lmatkows         ###   ########.fr       */
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

typedef struct s_win
{
	struct s_var	*var;
	void			*win_ptr;
	char			*title;
	int				width;
	int				height;
}	t_win;

typedef struct s_var
{
	void			*mlx_ptr;
	int				status;
	t_win			win;
	t_textures		txtr;
}	t_var;

#endif