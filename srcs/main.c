/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/29 11:21:27 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 2)
		return (ft_err("Error\nOne argument is expected\n"));
	if (!(ft_init_var(&var, argv[1]) && ft_parse(&var) && ft_init_window(&var)))
		return (ft_free_all(&var));
	ft_init_screen(&var);
	mlx_hook(var.win.win_ptr, KeyPress, KeyPressMask,
		ft_handle_keypress, (void *)(&var));
	mlx_hook(var.win.win_ptr, KeyRelease, KeyReleaseMask,
		ft_handle_keyrelease, (void *)(&var));
	mlx_hook(var.win.win_ptr, DestroyNotify, StructureNotifyMask,
		ft_close_n_free, (void *)&var);
	mlx_loop_hook(var.mlx_ptr, ft_repeat_key_events, (void *)&var);
	mlx_loop(var.mlx_ptr);
	ft_free_all(&var);
	return (0);
}
