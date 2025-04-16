/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/16 14:21:47 by juduchar         ###   ########.fr       */
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
	return (0);
}
