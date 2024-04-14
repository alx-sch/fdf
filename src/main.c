/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/14 13:54:12 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file implements the main() for the FDF program.

#include "fdf.h"

// FILE

int		main(int argc, char **argv);

// init_fdf.c

void	init_fdf(t_fdf *fdf, char *file);

// hooks.c

int		handle_keypress(int keycode, t_fdf *fdf);
int		handle_event(t_fdf *fdf);
int		close_window(t_fdf *fdf);

// render.c

int		render(t_fdf *fdf);

// utils.c

void	msg_and_exit(char *msg);
void	perror_and_exit(char *msg);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

// int	main(int argc, char **argv)
// {
// 	t_fdf		fdf;

// 	argc = 0;
// 	argv[0] = "";
// 	fdf.mlx_ptr = mlx_init();
// 	if (!fdf.mlx_ptr)
// 		msg_and_exit(ERR_MLX);
// 	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WINDOW_W, WINDOW_H, "TEST!");
// 	if (!fdf.win_ptr)
// 		msg_and_exit(ERR_MLX);

// 	fdf.img.img = mlx_new_image(fdf.mlx_ptr, WINDOW_W, WINDOW_H);
// 	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bpp,
// 			&fdf.img.line_len, &fdf.img.endian);
// 	mlx_loop_hook(fdf.mlx_ptr, &render, &fdf);

// 	mlx_hook(fdf.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &fdf);
// 	mlx_hook(fdf.win_ptr, DestroyNotify, 0, &close_window, &fdf); // 'x' in window is clicked

// 	mlx_loop(fdf.mlx_ptr);

// 	mlx_destroy_image(fdf.mlx_ptr, fdf.img.img);
// 	mlx_destroy_display(fdf.mlx_ptr);
// 	free(fdf.mlx_ptr);

// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		msg_and_exit(ERR_ARG, EXIT_ARG);
	init_fdf(&fdf, argv[1]);
	ft_printf("map_x: %d\n", fdf.map_x);
	ft_printf("map_y: %d\n", fdf.map_y);
	free(fdf.map);
}
