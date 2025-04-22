/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 15:20:39 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_init_img(t_var *var, t_img *img)
{
	img->img_ptr = mlx_new_image(var->mlx_ptr, var->win.width, var->win.height);
	img->bit_per_pix = 0;
	img->line_len = 0;
	img->endian = 0;
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bit_per_pix, &img->line_len, &img->endian);
	return (img);
}

void	ft_draw_point(t_var *var, int x, int y, int col, t_img *img)
{
	char	*ptr;

	if (x < 0 || x >= var->win.width || y < 0 || y >= var->win.height)
		return ;
	ptr = img->data_addr + (y * img->line_len) + x * (img->bit_per_pix / 8);
	*(int *)ptr = col;
}

double	ft_deg_to_rad(int angle_deg)
{
	return ((double)angle_deg * 2.0 * M_PI / 360.0);
}

void	ft_draw_disc(t_var *var, int x0, int y0, int col, t_img *img)
{
	int		r;
	int		x;
	int		y;
	int		angle;

	x0 = (x0 + 0.5) * var->zoom_mnm;
	y0 = (y0 + 0.5) * var->zoom_mnm; 
	r = var->zoom_mnm / 4;
	while (r > 0)
	{
		angle = 0;
		while (angle <= 360)
		{
			x = x0 + cos(ft_deg_to_rad(angle)) * r;
			y = y0 + sin(ft_deg_to_rad(angle)) * r;
			ft_draw_point(var, x, y, col, img);
			angle ++;
		}
		r--;
	}
}

void	ft_draw_line(t_var *var, t_img *img, t_pix p1, t_pix p2, int col)
{
	int	x;
	int	y;

	x = p1.x;
	y = p1.y;
	if (x == p2.x)
	{
		while (y != p2.y)
		{
			ft_draw_point(var, x, y, col, img);
			y++;
		}
	}
	else if (y == p2.y)
	{
		while (x != p2.x)
		{
			ft_draw_point(var, x, y, col, img);
			x++;
		}	
	}
	else
		printf("erreur\n");
}

int	ft_is_wall(int x, int y, t_map *map)
{
	if (x < map->size_x && y < map->size_y && map->tab[y][x] == '1')
		return (1);
	return(0);
}

void	ft_connect_nodes(t_var *var, t_img *img, int x, int y, int col)
{
	t_pix	p0;
	t_pix	p1;
	t_pix	p2;
	t_pix	p3;

	p0.x = x * var->zoom_mnm;
	p0.y = y * var->zoom_mnm;
	p1.x = p0.x + var->zoom_mnm;
	p1.y = p0.y;
	p2.x = p0.x;
	p2.y = p0.y + var->zoom_mnm;
	p3.x = p0.x + var->zoom_mnm;
	p3.y = p0.y + var->zoom_mnm;
	if (ft_is_wall(x, y, var->map) == 1)
	{
		if (p1.x <= var->map->size_x * var->zoom_mnm)
		{
			ft_draw_line(var, img, p0, p1, col);
			if (p2.y <= var->map->size_y * var->zoom_mnm)
				ft_draw_line(var, img, p2, p3, col);	
		}
		if (p2.y <= var->map->size_y * var->zoom_mnm)
		{
			ft_draw_line(var, img, p0, p2, col);
			if (p3.x <= var->map->size_x * var->zoom_mnm)
				ft_draw_line(var, img, p1, p3, col);	
		}
	}
}

int	ft_x_camera(t_var *var, int *ray_x, int *ray_y, int x)
{
	double	cam_x;

	cam_x = (2 * (double)x / (double)var->win.width - 1.0);
	*ray_x = var->play.or_x + var->plane.x * cam_x;
	*ray_y = var->play.or_y + var->plane.y * cam_x;
	return (0);
}

int	ft_set_plane(t_var *var)
{
	var->plane.x = -var->play.or_y * var->plane.len; 
	var->plane.y = var->play.or_x * var->plane.len; 
	return (0);
}

int	ft_build_screen(t_var *var)
{
	(void)var;
	return (0);
}

int	ft_handle_hook(int keyc, t_var *var)
{
	//printf("%d\n", keyc);
	if (keyc == 119 || keyc == 115)
		ft_move(var, keyc);
	if (keyc == 97 || keyc == 100)
		ft_rotate(var, keyc);
	if (keyc == 65307)
		ft_close_n_free(var);
	//printf("angle = %d\n", var->play.angle);
	//printf("or_x = %f\n", var->play.or_x);
	//printf("or_y = %f\n", var->play.or_y);
	return (0);
}

int	ft_draw_minimap(t_var *var)
{
	int		x;
	int		y;
	int		col;

	y = 0;
	x = 0;
	col = 0x0000FF;
	while (y <= var->map->size_y)
	{
		x = 0;
		while (x <= var->map->size_x)
		{
			if (x == var->play.pos_x && y == var->play.pos_y)
				ft_draw_disc(var, x, y, 0xFF0000, &var->mini_map);
			ft_connect_nodes(var, &var->mini_map, x, y, col);
			x++;
		}
		y++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;

	(void)argc;
	if (!(ft_init_var(&var, argv[1]) && ft_parse(&var) && ft_init_window(&var)))
		return (ft_free_all(&var));
	ft_init_img(&var, &(var.mini_map));
	ft_draw_minimap(&var);
	printf("win width %d\n", var.win.width);
	printf("win height %d\n", var.win.height);
	printf("map size x %d\n", var.map->size_x);
	printf("map size y %d\n", var.map->size_y);
	mlx_put_image_to_window(var.mlx_ptr, var.win.win_ptr, var.mini_map.img_ptr, var.win.width - (var.map->size_x + 2) * var.zoom_mnm, var.win.height - (var.map->size_y + 2) * var.zoom_mnm);
	//ft_print_parsed_data(&var);
	mlx_hook(var.win.win_ptr, 17, 0, ft_close_n_free, (void *)(&var));
	mlx_key_hook(var.win.win_ptr, ft_handle_hook, (void *)(&var));
	mlx_loop(var.mlx_ptr);
	ft_free_all(&var);
	return (0);
}
