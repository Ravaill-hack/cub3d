/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/17 14:21:07 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_n_free(void *v)
{
	t_var	*var;

	var = (t_var *)v;
	ft_free_all(var);
	exit(0);
}

int	ft_handle_hook(int keyc, t_var *var)
{
	if (keyc == 65307)
		ft_close_n_free(var);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;

	(void)argc;
	if (!(ft_init_var(&var, argv[1]) && ft_parse(&var) && ft_init_window(&var)))
		return (ft_free_all(&var));
	ft_print_parsed_data(&var);
	mlx_hook(var.win.win_ptr, 17, 0, ft_close_n_free, (void *)(&var));
	mlx_key_hook(var.win.win_ptr, ft_handle_hook, (void *)(&var));
	mlx_loop(var.mlx_ptr);
	ft_free_all(&var);
	return (0);
}
