/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:11:30 by julien            #+#    #+#             */
/*   Updated: 2025/04/22 18:12:05 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:18:25 by julien            #+#    #+#             */
/*   Updated: 2025/02/12 14:12:43 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*int	ft_handle_keypress(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < KEY_MAX)
		data->input.keys[keycode] = 1;
	if (keycode == KEY_CENTER)
		ft_center_map(data);
	if (keycode == KEY_MIRROR)
	{
		data->render.scale = -data->render.scale;
		data->need_redraw = 2;
	}
	if (data->input.keys[KEY_ORTHOGONAL]
		|| data->input.keys[KEY_ISOMETRIC] || data->input.keys[KEY_CONIC])
		ft_handle_keys_change_projection(data);
	if (data->input.keys[KEY_CLOSE])
		ft_handle_close(data);
	return (0);
}

int	ft_handle_keyrelease(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < KEY_MAX)
		data->input.keys[keycode] = 0;
	return (0);
}

void	ft_handle_repeat_keys_all_projections(t_data *data)
{
	if (data->input.keys[KEY_ZOOM_IN] || data->input.keys[KEY_ZOOM_IN_2]
		|| data->input.keys[KEY_ZOOM_OUT] || data->input.keys[KEY_ZOOM_OUT_2])
		ft_handle_keys_zoom(data);
	if (data->input.keys[KEY_MOVE_UP] || data->input.keys[KEY_MOVE_DOWN]
		|| data->input.keys[KEY_MOVE_LEFT] || data->input.keys[KEY_MOVE_RIGHT])
		ft_handle_keys_translation(data);
	if (data->input.keys[KEY_DECREASE_SCALE_Z])
		data->render.render_isometric.scale_z
			= data->render.render_isometric.scale_z
			- (float)((float)SCALE_Z_STEP / 10);
	if (data->input.keys[KEY_INCREASE_SCALE_Z])
		data->render.render_isometric.scale_z
			= data->render.render_isometric.scale_z + SCALE_Z_STEP;
	data->need_redraw = 2;
}

int	ft_repeat_key_events(t_data *data)
{
	if (data->input.keys[KEY_CENTER] || data->input.keys[KEY_MIRROR]
		|| data->input.keys[KEY_ORTHOGONAL]
		|| data->input.keys[KEY_ISOMETRIC] || data->input.keys[KEY_CONIC]
		|| data->input.keys[KEY_CLOSE])
		return (0);
	ft_handle_repeat_keys_all_projections(data);
	if (data->render.projection == ISOMETRIC_PROJECTION)
		ft_handle_keys_isometric_projection(data);
	if (data->render.projection == CONIC_PROJECTION)
		ft_handle_keys_conic_projection(data);
	if (data->input.keys[KEY_CHANGE_COLOR])
		ft_change_color(data);
	ft_update_image(data);
	return (0);
}
*/