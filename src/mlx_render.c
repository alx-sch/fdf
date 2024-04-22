/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/22 21:29:14 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "fdf.h"

void	render_image(t_fdf *fdf);

/*
Sets the color of a pixel at a specified position within the image buffer.
Calculates the memory location (pixel) where the color value will be stored
in the image buffer. The function then assigns the color value at that
buffer location. Used as a more performative alternative to of mlx_pixel_put().
Source: https://harm-smits.github.io/42docs/libs/minilibx.
*/
static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + ((y) * img->size_len + (x) * (img->bpp / 8));
	*(int *)pixel = color;
}

// Fills the entire image with a preset background color.
static void	render_background(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_H)
	{
		j = 0;
		while (j < WINDOW_W)
			img_pix_put(&fdf->img, j++, i, BG_COLOR);
		i++;
	}
}

void	render_image(t_fdf *fdf)
{
	int x = 0;
	int y = 0;

	render_background(fdf);
	get_projected_coordinates(fdf);

	while (y < fdf->y_max)
	{
		while (x < fdf ->x_max)
		{
			img_pix_put(&fdf->img, fdf->x_proj[y][x], fdf->y_proj[y][x], fdf->color[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
