/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:19:41 by julien            #+#    #+#             */
/*   Updated: 2025/04/29 12:34:06 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_txtr_var(t_textures *txtr)
{
	txtr->no_img.img_ptr = NULL;
	txtr->so_img.img_ptr = NULL;
	txtr->we_img.img_ptr = NULL;
	txtr->ea_img.img_ptr = NULL;
	txtr->no_img.path = NULL;
	txtr->so_img.path = NULL;
	txtr->we_img.path = NULL;
	txtr->ea_img.path = NULL;
	txtr->fl_col = 0;
	txtr->ce_col = 0;
}

int	ft_init_one_txt(t_var *var, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(var->mlx_ptr, img->path, &img->width,
			&img->height);
	if (!img->img_ptr)
		return (ft_err(ERR_TEXTR_PATH));
	img->data_addr = mlx_get_data_addr(img->img_ptr, &(img->bit_per_pix),
			&(img->line_len), &(img->endian));
	if (!img->data_addr)
		return (ft_err(ERR_TEXTR_PATH));
	return (1);
}

t_textures	*ft_init_txtr(t_var *var)
{
	if (!ft_init_one_txt(var, &(var->txtr.so_img))
		|| !ft_init_one_txt(var, &(var->txtr.no_img))
		|| !ft_init_one_txt(var, &(var->txtr.we_img))
		|| !ft_init_one_txt(var, &(var->txtr.ea_img)))
		return (NULL);
	return (&var->txtr);
}
