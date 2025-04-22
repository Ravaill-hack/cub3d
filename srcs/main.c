/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/04/22 10:00:24 by lmatkows         ###   ########.fr       */
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

int	ft_rotate(t_var *var, int keyc)
{
	if (keyc == 97)
		var->play.angle = (var->play.angle + 1) % 360;
	else if (keyc == 100)
		var->play.angle = (var->play.angle - 1) % 360;
	else
		return (1);
	var->play.or_x = cos((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	var->play.or_y = sin((double)(var->play.angle) * 2.0 * M_PI / 360.0);
	return (0);
}

int	ft_move(t_var *var, int keyc)
{
	if (keyc == 119)
		var->play.forw ++;
	else if (keyc == 115)
		var->play.bckw ++;
	else
		return (1);
	return (0);
}

int	ft_handle_hook(int keyc, t_var *var)
{
	printf("%d\n", keyc);
	if (keyc == 119 || keyc == 115)
		ft_move(var, keyc);
	if (keyc == 97 || keyc == 100)
		ft_rotate(var, keyc);
	if (keyc == 65307)
		ft_close_n_free(var);
	printf("angle = %d\n", var->play.angle);
	printf("or_x = %f\n", var->play.or_x);
	printf("or_y = %f\n", var->play.or_y);
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
