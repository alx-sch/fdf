/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/11 21:19:10 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file implements the main() for the FDF program.

#include "fdf.h"

// FILE
int		main(int argc, char **argv);

// map.c
int		check_filename(char *s);
int		get_map_x(char *file);
int		get_map_y(char *file);
int		is_map_rect(char *file, int map_x);

// hooks.c
int		handle_keypress(int keycode, t_fdf *fdf);
int		handle_event(t_fdf *fdf);

// render.c
int		render(t_fdf *fdf);

// utils.c
void	msg_and_exit(char *msg, int exit_code);

// libft


//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

// int	main(void)
// {
// 	t_fdf		fdf;

// 	fdf.mlx_ptr = mlx_init();
// 	if (!fdf.mlx_ptr)
// 		msg_and_exit("MLX ERROR\n", MLX_ERROR);
// 	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WINDOW_W, WINDOW_H, "TEST!");
// 	if (!fdf.win_ptr)
// 		msg_and_exit("MLX ERROR\n", MLX_ERROR);

// 	fdf.img.img = mlx_new_image(fdf.mlx_ptr, WINDOW_W, WINDOW_H);
// 	fdf.img.addr = mlx_get_fdf_addr(fdf.img.img, &fdf.img.bpp,
// 			&fdf.img.line_len, &fdf.img.endian);
// 	mlx_loop_hook(fdf.mlx_ptr, &render, &fdf);
// 	mlx_hook(fdf.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &fdf);

// 	mlx_loop(fdf.mlx_ptr);

// 	mlx_destroy_image(fdf.mlx_ptr, fdf.img.img);
// 	mlx_destroy_display(fdf.mlx_ptr);
// 	free(fdf.mlx_ptr);

// 	return (0);
// }

int	main(int argc, char **argv)
{
	int	x = get_map_x(argv[1]);
	int	y = get_map_y(argv[1]);

	if (argc != 2)
		msg_and_exit(ERR_ARG, EXIT_ARG);
	if (!check_filename(argv[1]))
		msg_and_exit(ERR_FILE, EXIT_FILE);
	ft_printf("map_x: %d\n", x);
	ft_printf("map_y: %d\n", y);
	ft_printf("map_rect: %d\n", is_map_rect(argv[1], x));

}
