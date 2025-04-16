/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 16:54:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_var	var;

	(void)argc;
	if (!ft_init_var(&var, argv[1]))
		return (1);
	if (!ft_parse(&var))
		return (1);
	if (!ft_init_window(&var))
		return (1);
	ft_print_parsed_data(&var);
	mlx_loop(var.mlx_ptr);
	ft_free_all(&var);
	return (0);
}
