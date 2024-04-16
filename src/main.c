/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/16 20:33:21 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file implements the main() for the FDF program.

#include "fdf.h"

// FILE

int		main(int argc, char **argv);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Checks user input and passed file.
Prints error message and terminates the program, if:
 - Not exactly one argument is passed.
 - The passed file cannot be opened (e.g., does not exist or no read rights).
 - The passed file does not have the '.fdf' extension.
*/
static void	check_file(int argc, char **argv)
{
	int	fd;
	int	len;

	if (argc != 2)
		msg_and_exit(ERR_ARG, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror_and_exit(argv[1], NULL);
	close (fd);
	len = ft_strlen(argv[1]);
	while (len >= 0 && argv[1][len] != '.')
		len--;
	if (ft_strcmp(argv[1] + len, ".fdf"))
		msg_and_exit(ERR_FILE_TYPE, NULL);
}

/*
Initializing map members in the fdf structure to NULL / zero.
This helps to avoid accessing variables that are not initialized.
*/
static void	null_map(t_fdf *fdf)
{
	fdf->map_x = 0;
	fdf->map_y = 0;
	fdf->map_z = NULL;
	fdf->map_color = NULL;
	fdf->color_provided = 0;
	fdf->fd = -1;
	fdf->line = NULL;
}

/*
Initialiazes map members of the'fdf' structure:
- Map width (fdf->map_x)
- Map height (fdf->map_y)
- Map depth (fdf->map_z)
*/
static void	init_map(t_fdf *fdf, char *file)
{
	null_map(fdf);
	get_map_x_and_y(fdf, file);
	get_map_z(fdf, file);
	get_map_color(fdf, file);
}

/*
Initialiazes graphic-related members of the 'fdf' structure:
- The connection to the graphic system (fdf->mlx)
- The window (fdf->win)
- The image buffer (fdf->img)
*/
static void	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		msg_and_exit(ERR_MLX, fdf);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!fdf->win)
		msg_and_exit(ERR_MLX, fdf);
	fdf->img.img = mlx_new_image(fdf->mlx, WINDOW_W, WINDOW_H);
	fdf->img.data = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.size_len, &fdf->img.endian);
}

//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

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
	t_fdf		fdf;

	check_file(argc, argv);
	init_map(&fdf, argv[1]);
	init_mlx(&fdf);

	render_image(&fdf);

///
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
///

	mlx_destroy_image(fdf.mlx, fdf.img.img);
	mlx_destroy_display(fdf.mlx);
	free(fdf.mlx);

	// if (fdf.mlx)
	// {
	// 	if (fdf.img.img)
	// 		mlx_destroy_image(fdf.mlx, fdf.img.img);
	// 	mlx_destroy_display(fdf.mlx);
	// 	free(fdf.mlx);
	// }
	free_map(&fdf);
	//free_mlx(&fdf);
	exit(EXIT_SUCCESS);
}

// int	main(int argc, char **argv)
// {
// 	t_fdf	fdf;

// 	check_file(argc, argv);
// 	init_fdf(&fdf, argv[1]);

// 	ft_printf("map_x: %d\n", fdf.map_x);
// 	ft_printf("map_y: %d\n", fdf.map_y);

// 	ft_printf("\nZ values:\n");
// 	print_int_2d_array(fdf.map_z, fdf.map_y, fdf.map_x);

// 	ft_printf("\nColor values:\n");
// 	print_int_2d_array(fdf.map_color, fdf.map_y, fdf.map_x);

// 	// if (fdf.color_provided)
// 	// 	ft_printf("\nColor provided!\n");
// 	// else
// 	// 	ft_printf("\nColor NOT provided!\n");


// 	//ft_printf("\n0xFF0000 as int: %d\n", ft_atoi_base("FF0000", 16));

// 	free_fdf(&fdf);
// 	exit(EXIT_SUCCESS);
// }
