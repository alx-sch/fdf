/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/22 21:00:46 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "fdf.h"

// IN FILE:

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
Initializing map members in the fdf structure to starting values.
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
	fdf->x_proj_max = 0;
	fdf->y_proj_max = 0;
	fdf->x_proj_min = FLT_MAX;
	fdf->y_proj_min = FLT_MAX;
	fdf->x_proj = NULL;
	fdf->y_proj = NULL;
	fdf->mlx = NULL;
}

/*
Initial assignment of members of the 'fdf' structure:
- Map width (fdf->x_max; int)
- Map height (fdf->y_max; int)
- Map depth (fdf->z; int**)
- Map color (fdf->color; int **)
- The connection to the graphic system (fdf->mlx; void *)
- The window (fdf->win; void *)
- The image buffer (fdf->img; t_img)
*/
static void	parse_map_and_init_mlx(t_fdf *fdf, char *file)
{
	null_fdf(fdf);
	get_x_and_y(fdf, file);
	get_z(fdf, file);
	get_color(fdf, file);
	//allocate_memory_for_projection(fdf);
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

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	check_file(argc, argv);
	parse_map_and_init_mlx(&fdf, argv[1]);
	render_image(&fdf);
	mlx_key_hook(fdf.win, &handle_keypress, &fdf);
	mlx_hook(fdf.win, DestroyNotify, 0, &handle_x, &fdf);
	mlx_loop(fdf.mlx);
	printf("RIGHT\n");
	ft_printf("TEST\n");
	exit(EXIT_SUCCESS);
}
