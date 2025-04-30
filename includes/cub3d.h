/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:57:45 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/30 13:17:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <X11/X.h>

# define KEY_W 		119
# define KEY_A 		97
# define KEY_S 		115
# define KEY_D		100
# define KEY_RGT	65363
# define KEY_LFT	65361
# define KEY_ESC	65307

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
# define ERR_FILE_EXTENSION "Error\nInvalid file extension for map file\n"
# define ERR_FILE_EMPTY "Error\nError file is empty\n"
/*
Texture errors
*/
# define ERR_TEXTR_PATH "Error\nIncorrect path for textures\n"
# define ERR_TEXTR_MISSING_DATA "Error\nTexture data are missing\n"
# define ERR_TEXTR_NO_MISSING "Error\nNorth texture is missing\n"
# define ERR_TEXTR_SO_MISSING "Error\nSouth texture is missing\n"
# define ERR_TEXTR_WE_MISSING "Error\nWest texture is missing\n"
# define ERR_TEXTR_EA_MISSING "Error\nEast texture is missing\n"
# define ERR_TEXTR_SYNTAX "Error\nInvalid texture syntax\n"
/*
Color errors
*/
# define ERR_COLORS_MISSING_DATA "Error\nColors data are missing\n"
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
# define ERR_MAP_NO_PLAY "Error\nNo player on the map\n"
# define ERR_MAP_PLAYERS "Error\nThere must be only one player\n"
# define ERR_MAP_SYNTAX "Error\nInvalid character in the map\n"
# define ERR_MAP_BOUND "Error\nA wall is open on the boundaries\n"

typedef struct s_double_points
{
	double	x;
	double	y;
}	t_double_points;

typedef struct s_end
{
	double		x;
	double		y;
	double		x_st;
	double		y_st;
	int			tmp;
}	t_end;

typedef struct s_pix
{
	int				x;
	int				y;
	int				z;
	unsigned int	col;
}	t_pix;

typedef struct s_angles
{
	t_pix			p0;
	t_pix			p1;
	t_pix			p2;
	t_pix			p3;
}	t_angles;

typedef struct s_ray
{
	t_pix			t_node;
	int				wall;
	double			target_dist;
	int				target_height;
	int				ray_width;
	double			angle;
}	t_ray;

typedef struct s_colors
{
	int				col_int;
	int				r;
	int				v;
	int				b;
	int				i;
}	t_colors;

typedef struct s_plane
{
	int				fov_deg;
	double			fov_rad;
	double			x;
	double			y;
	double			len;
	int				h_wall;
}	t_plane;

typedef struct s_player
{
	double			or_x;
	double			or_y;
	int				angle;
	//double		forw;
	double			pos_x;
	double			pos_y;
}	t_player;

typedef struct s_img
{
	struct s_var	*var; //peut etre pas necessaire
	void			*img_ptr;
	char			*data_addr;
	char			*path;
	int				bit_per_pix;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	int				off_x;
	int				off_y;
}	t_img;

typedef struct s_xpm_draw
{
	int				x_txt;
	t_img			*txt;
	double			v_step;
	int				y_txt;
	int				col;
	int				i_y;
}	t_xpm_draw;

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

typedef struct s_input
{
	int				key_w;	//forward
	int				key_a;	//step aside left
	int				key_s;	//backward
	int				key_d;	//step aside right
	int				key_lft;//left rotation
	int				key_rgt;//right rotation
}	t_input;

typedef struct s_line
{
	t_pix			pixel_1;
	t_pix			pixel_2;
}		t_line;

typedef struct s_bresenham
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}	t_bresenham;

typedef struct s_var
{
	void			*mlx_ptr;
	int				status; //a supprimer
	int				zoom;
	double			step;
	double			ratio_horizon; // compris entre 0 et 1
	double			dist_to_plane;
	//char			*background_save;
	// pour ne pas avoir a recalculer le fond a chaque fois
	t_win			win;
	t_textures		txtr;
	t_map			*map;
	t_player		play;
	t_plane			plane;
	t_img			screen;
	t_img			mini_map;
	t_input			input;
	int				need_redraw;
}	t_var;

/*
Initialization (init.c)
*/
void		ft_init_plane(t_plane *plane);
int			ft_init_window(t_var *var);
void		ft_init_inputs(t_input *input);
int			ft_init_var(t_var *var, char *title);
/*
Textures initialization (init_textures.c)
*/
int			ft_init_one_txt(t_var *var, t_img *img);
t_textures	*ft_init_txtr(t_var *var);
void		ft_init_txtr_var(t_textures *txtr);
/*
Img init (init_img.c)
*/
t_img		*ft_init_img(t_var *var, t_img *img);
int			ft_init_background(t_var *var);
int			ft_init_screen(t_var *var);
int			ft_draw_floor(t_var *var, t_img *img, t_pix *p);
int			ft_draw_ceiling(t_var *var, t_img *img, t_pix *p);
/*
Error (error.c)
*/
int			ft_err(char *str);
void		*ft_err_null(char *str);
/*
Parsing (parsing.c)
*/
void		ft_go_to_end_fd(int fd);
void		*ft_parse(t_var *var);
/*
Map parsing (parsing_map.c)
*/
char		*ft_go_to_map_first_line(int fd, char *tmp);
void		*ft_process_map_char(t_var *var, char c, int x, int y);
void		*ft_append_map_line(t_var *var, char *ln, int y);
void		*ft_allocate_map_tab(t_var *va);
void		*ft_parse_map(t_var *var, int fd, char **line);
/*
Color parsing (parsing_colors.c)
*/
int			ft_convert_color(char *str);
void		*ft_parse_colors(t_var *var, char *line, int *i);
int			ft_darker_pix(int col, int dist);
/*
Parsing textures (parsing_textures.c)
*/
int			ft_is_xpm(char *str);
int			ft_valid_txtr(t_var *var);
void		*ft_parse_textures(t_var *var, char *line, int *i);
/*
Parsing utils (parsing_utils.c)
*/
int			ft_map_size_x(t_var *var);
int			ft_map_size_y(t_var *var);
int			ft_is_valid_map_size(t_var *var);
int			ft_find_angle(char c, t_var *var);
char		*ft_extract_title(char *path);
/*
Map checker (map_checker.c)
*/
int			ft_check_if_exists(t_map *map, char **tab, int x, int y);
int			ft_is_valid_map(t_map *map, t_var *var);
/*
Textures drawing (draw_textures.c)
*/
int			ft_error_texture(int wall);
int			ft_find_texture(t_var *var, t_ray *ray, int *x, t_img **txt);
int			ft_draw_column(t_var *var, t_ray *ray, t_img *img, t_line line);
/*
Drawing (draw_utils.c)
*/
void		ft_draw_point(t_var *var, t_pix point, int col, t_img *img);
void		ft_draw_line_map(t_var *var, t_img *img, t_line line, int col);
void		ft_draw_disc(t_var *var, t_pix p0, int col, t_img *img);
void		ft_init_points(t_angles *a, t_var *var, int x, int y);
void		ft_connect_nodes(t_var *var, t_img *img, t_pix n, int col);
/*
Drawing (draw_utils_2.c)
*/
void		ft_draw_nodes(t_var *var);
t_line		ft_build_line(t_pix p1, t_pix p2);
int			ft_draw_background(t_var *var, t_img *img);
/*
Drawing lines (draw_line_bres.c)
*/
void		ft_set_bres_sx_sy(t_bresenham *bres, t_line line);
void		ft_update_bres(t_bresenham *bres, t_pix *pixel);
void		ft_draw_horizontal(t_var *var, t_line line, int col, t_img *img);
void		ft_draw_vertical(t_var *var, t_line line, int col, t_img *img);
void		ft_draw_line_bres(t_var *var, t_line line, t_img *img);
/*
Minimap (minimap_utils.c)
*/
int			ft_is_close_to_player(t_var *var, int x, int y);
void		ft_draw_player(t_var *var);
void		ft_draw_nodes(t_var *var);
/*
Minimap utils (minimap_utils.c)
*/
int			ft_is_close_to_player(t_var *var, int x, int y);
int			ft_is_zoom_wall(t_double_points p, t_map *map, int zoom, char c);
int			ft_check_wall(double x, double y, t_map *map, int zoom);
void		ft_draw_player(t_var *var);
int			ft_wall_type(double delta_x, double delta_y, char c);
/*
Update image (update_image.c)
*/
int			ft_put_image_to_window(t_var *var, t_img *img);
int			ft_update_image(t_var *var);
/*
Handle keys (handle_keys.c)
*/
int			ft_handle_keypress(int keycode, t_var *var);
int			ft_handle_keyrelease(int keycode, t_var *var);
void		ft_handle_key_move(t_var *var, t_input input);
int			ft_repeat_key_events(t_var *var);
/*
Actions (actions.c)
*/
int			ft_close_n_free(void *v);
int			ft_rotate(t_var *var, int keyc);
void		ft_check_wall_collision(t_var *var,
				double new_pos_x, double new_pos_y);
int			ft_move(t_var *var, int keyc);
int			ft_build_image(t_var *var);
/*
Free (free.c)
*/
int			ft_free_win(t_var *var);
int			ft_free_txtr(t_var *var);
int			ft_free_map(t_var *var);
int			ft_free_all(t_var *var);
/*
Utils (utils.c)
*/
int			ft_line_is_empty(char *line);
char		*ft_free_line_go_to_next_line(int fd, char *line);
char		ft_first_char(char *str);
char		*ft_special_strdup(char *str);
/*
Utils (utils2.c)
*/
int			ft_intercept_wall(int x, int y, t_map *map);
int			ft_intercept_unseen_wall(int x, int y, t_map *map);
int			ft_is_wall(int x, int y, t_map *map);
int			ft_is_unseen_wall(int x, int y, t_map *map);
int			ft_strict_check_wall(double x, double y, t_map *map);
/*
Algebre utils (algebre_utils.c)
*/
int			ft_min(int x1, int x2);
int			ft_max(int x1, int x2);
/*
Geometry utils (geometry_utils.c)
*/
int			ft_find_orientation(t_var *var);
double		ft_distance(t_pix p1, t_pix p2);
double		ft_distance_double(double x1, double y1, double x2, double y2);
double		ft_deg_to_rad(double angle_deg);
int			ft_find_end(t_var *var, double or_x, double or_y, t_ray *ray);
/*
Raycasting (raycasting.c)
*/
int			ft_calculate_ray(t_var *var, t_ray *ray, double angle);
int			ft_draw_ray(t_var *var, t_ray ray, int x);
int			ft_draw_vector(t_var *var, double angle, t_ray *ray);
int			ft_draw_screen(t_var *var);

#endif