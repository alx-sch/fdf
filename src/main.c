/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/10 18:44:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file implements the main() for the FDF program.

#include "fdf.h"

// FILE
int		main(void);

// hooks.c
int		handle_keypress(int keycode, t_data *data);

// render.c
int		render(t_data *data);

// utils.c
void	msg_and_exit(char *msg, int exit_code);

//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		msg_and_exit("MLX ERROR\n", MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_W, WINDOW_H, "TEST!");
	if (!data.win_ptr)
		msg_and_exit("MLX ERROR\n", MLX_ERROR);

	data.img.img = mlx_new_image(data.mlx_ptr, WINDOW_W, WINDOW_H);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_image(data.mlx_ptr, data.img.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);

	return (0);
}
