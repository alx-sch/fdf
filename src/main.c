/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 19:13:39 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file implements the main() for the FDF program.

#include "fdf.h"

// FILE

int		main(int argc, char **argv);

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
// 	fdf.mlx = mlx_init();
// 	if (!fdf.mlx)
// 		msg_and_exit(ERR_MLX, &fdf);
// 	fdf.win = mlx_new_window(fdf.mlx, WINDOW_W, WINDOW_H, "TEST!");
// 	if (!fdf.win)
// 		msg_and_exit(ERR_MLX, &fdf);

// 	fdf.img.img = mlx_new_image(fdf.mlx, WINDOW_W, WINDOW_H);
// 	fdf.img.data = mlx_get_data_addr(fdf.img.img, &fdf.img.bpp,
// 			&fdf.img.size_len, &fdf.img.endian);
// 	mlx_loop_hook(fdf.mlx, &render, &fdf);

// 	mlx_hook(fdf.win, KeyPress, KeyPressMask, &handle_keypress, &fdf);
// 	mlx_hook(fdf.win, DestroyNotify, 0, &close_window, &fdf); // 'x' in window is clicked

// 	mlx_loop(fdf.mlx);

// 	mlx_destroy_image(fdf.mlx, fdf.img.img);
// 	mlx_destroy_display(fdf.mlx);
// 	free(fdf.mlx);

// 	exit(EXIT_SUCCESS);
// }

void print_int_2d_array(int **array, int rows, int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			ft_printf("%d ", array[i][j]);
		}
		ft_printf("\n");
	}
}


int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		msg_and_exit(ERR_ARG, NULL);
	init_fdf(&fdf, argv[1]);
	ft_printf("map_x: %d\n", fdf.map_x);
	ft_printf("map_y: %d\n", fdf.map_y);

	ft_printf("\nZ values:\n");
	print_int_2d_array(fdf.map_z, fdf.map_y, fdf.map_x);

	ft_printf("\nColor values:\n");
	print_int_2d_array(fdf.map_color, fdf.map_y, fdf.map_x);

	if (fdf.color_provided)
		ft_printf("\nColor provided!\n");
	else
		ft_printf("\nColor NOT provided!\n");


	ft_printf("\n0xFF0000 as int: %d\n", ft_atoi_base("FF0000", 16));

	free_fdf(&fdf);
	exit(EXIT_SUCCESS);
}
