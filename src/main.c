/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/10 14:21:19 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file implements the main() for the FDF program.

#include "fdf.h"

// FILE
int		main(void);

// libft
int		ft_printf(const char *format, ...);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++


//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

void	my_mlx_square_put(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
	// Iterate over the square area and fill each pixel with the specified color
	for (int i = y; i < y + size; i++)
	{
		for (int j = x; j < x + size; j++)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, j, i, color);
			//my_mlx_pixel_put(data, j, i, color);
		}
	}
}

int	create_color(int transparency, int red, int green, int blue)
{
	return (transparency << 24 | red << 16 | green << 8 | blue);
}

//
//
//

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WINDOW_W, WINDOW_H, "TEST!");

	my_mlx_square_put(mlx, mlx_win, 100, 100, 50, create_color(255, 255, 255, 255));

	mlx_loop(mlx);

	return (0);
}

/* using img
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	if (!mlx)
		return (1);

	mlx_win = mlx_new_window(mlx, 960, 540, "Hello world!");
	if (!mlx_win)
		return (1);

	img.img = mlx_new_image(mlx, 960, 540);
	if (!img.img)
		return (1);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
			&img.endian);

	my_mlx_square_put_2(mlx, mlx_win, 100, 100, 50, create_trgb(0, 100, 0, 100));
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
*/
