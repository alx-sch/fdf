/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/09 17:24:06 by aschenk          ###   ########.fr       */
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


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_square_put(t_data *data, int x, int y, int size, int color)
{
	// Iterate over the square area and fill each pixel with the specified color
	for (int i = y; i < y + size; i++)
	{
		for (int j = x; j < x + size; j++)
		{
			my_mlx_pixel_put(data, j, i, color);
		}
	}
}


int	create_trgb(int transparency, int red, int green, int blue)
{
	return (transparency << 24 | red << 16 | green << 8 | blue);
}


// XXX
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 960, 540, "Hello world!");
	img.img = mlx_new_image(mlx, 960, 540);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);

	my_mlx_square_put(&img, 100, 100, 50, create_trgb(0, 100, 100, 100));
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

}
