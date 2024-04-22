/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/22 21:12:26 by aschenk          ###   ########.fr       */
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

static void	render_proj_coordinates(t_fdf *fdf)
{
	int		x;
	int		y;
	float	x_proj;
	float	y_proj;

	x = 0;
	y = 0;
	calculate_projection_paramters(fdf);
	while (y < fdf->y_max)
	{
		while (x < fdf ->x_max)
		{
			x_proj = (((x - y) * cos(ANGLE * M_PI / 180)) - fdf->x_proj_min)
				* fdf->scale + fdf->x_offset;
			y_proj = (((x + y) * sin(ANGLE * M_PI / 180) - fdf->z[y][x] * Z_S)
					- fdf->y_proj_min) * fdf->scale + fdf->y_offset;
			img_pix_put(&fdf->img, x_proj, y_proj, fdf->color[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}

void	render_image(t_fdf *fdf)
{
	render_background(fdf);
	render_proj_coordinates(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
