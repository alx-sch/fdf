/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/21 23:32:49 by aschenk          ###   ########.fr       */
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
This helps to avoid accessing variables that are not initialized, e.g.
in free_fdf() which is automatically called throughout the program once
the program terminates due to an error.
*/
static void	null_fdf(t_fdf *fdf)
{
	fdf->x_max = 0;
	fdf->y_max = 0;
	fdf->z = NULL;
	fdf->color = NULL;
	fdf->color_provided = 0;
	fdf->fd = -1;
	fdf->line = NULL;
	fdf->mlx = NULL;
	fdf->x_proj_max = 0;
	fdf->y_proj_max = 0;
	fdf->x_proj_min= FLT_MAX;
	fdf->y_proj_min = FLT_MAX;
}

/*
Initialiazes members of the'fdf' structure:
- Initializing
- Map width (fdf->map_x)
- Map height (fdf->map_y)
- Map depth (fdf->map_z)
- The connection to the graphic system (fdf->mlx)
- The window (fdf->win)
- The image buffer (fdf->img)
*/
static void	init_fdf(t_fdf *fdf, char *file)
{
	null_fdf(fdf);
	get_x_and_y(fdf, file);
	get_z(fdf, file);
	get_color(fdf, file);
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


// static int	handle_events(t_fdf *fdf)
// {
// 	if (fdf->close_window)
// 	{
// 		mlx_destroy_window(fdf->mlx, fdf->win);
// 		fdf->win = NULL;
// 		mlx_loop_end(fdf->mlx);
// 	}
// 	return (0);
// }

/*
Initialiazes graphic-related members of the 'fdf' structure:
- The connection to the graphic system (fdf->mlx)
- The window (fdf->win)
- The image buffer (fdf->img)
*/


//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

// void print_int_2d_array(int **array, int rows, int cols)
// {
// 	for (int i = 0; i < rows; i++) {
// 		for (int j = 0; j < cols; j++) {
// 			ft_printf("%d ", array[i][j]);
// 		}
// 		ft_printf("\n");
// 	}
// }

// int my_keyhook(int keycode, void *param)
// {
//     t_fdf *fdf = (t_fdf *)param;

//     // Check if the Escape key (keycode 53) is pressed
//     if (keycode == 53)
//     {
//         printf("ESCP PRESSED\n");
//         mlx_destroy_window(fdf->mlx, fdf->win);
//         exit(EXIT_SUCCESS); // Exit the program
//     }

//     return 0; // Return 0 to indicate that the event was handled successfully
// }

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	check_file(argc, argv);
	init_fdf(&fdf, argv[1]);

	render_image(&fdf);

	mlx_key_hook(fdf.win, &handle_keypress, &fdf);
	mlx_hook(fdf.win, DestroyNotify, 0, &handle_x, &fdf);
	mlx_loop(fdf.mlx);
	printf("RIGHT\n");
	ft_printf("TEST\n");
	exit(EXIT_SUCCESS);
}


// int	main(int argc, char **argv)
// {
// 	t_fdf		fdf;

// 	check_file(argc, argv);
// 	init_fdf(&fdf, argv[1]);
// ///
// 	ft_printf("map_x: %d\n", fdf.map_x);
// 	ft_printf("map_y: %d\n", fdf.map_y);

// 	// ft_printf("\nZ values:\n");
// 	// print_int_2d_array(fdf.map_z, fdf.map_y, fdf.map_x);

// 	// ft_printf("\nColor values:\n");
// 	// print_int_2d_array(fdf.map_color, fdf.map_y, fdf.map_x);

// 	if (fdf.color_provided)
// 		ft_printf("\nColor provided!\n");
// 	else
// 		ft_printf("\nColor NOT provided!\n");



// 	render_image(&fdf);

// 	mlx_key_hook(fdf.mlx, &my_keyhook, &fdf);

// 	mlx_loop(fdf.mlx);

// 	free_fdf(&fdf);
// 	exit(EXIT_SUCCESS);
// }

	// mlx_hook(fdf.win, DestroyNotify, 0, &close_window, &fdf);
	// mlx_hook(fdf.win, KeyPress, KeyPressMask, &handle_keypress, &fdf);
	// mlx_loop_hook(fdf.mlx, &handle_events, &fdf);

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




// int main(int argc, char **argv)
// {
//     t_vars vars;
// 	t_fdf fdf;

// 	check_file(argc, argv);
// 	init_fdf(&fdf, argv[1]);
//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, 800, 600, "Window");
//     mlx_key_hook(vars.win, close_window, &vars);
//     mlx_loop(vars.mlx);
//     return (0);
// }
