/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/21 23:55:55 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_image(t_fdf *fdf);

//	Sets the color of a pixel at a specified position within an image buffer.
//	Calculates the memory location (pixel) where the color value will be stored
//	in the image buffer. The function then stores the color value at that
//	location in the image buffer.
static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + ((y) * img->size_len + (x) * (img->bpp / 8));
	*(int *)pixel = color;
}

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

// scaling and offset -> whole map fits into window
// static void	get_extrema(t_fdf *fdf)
// {
// 	int	x;
// 	int	y;
// 	int	x_proj;
// 	int	y_proj;

// 	x = -1;
// 	y = -1;
// 	while (++y < fdf->y_max)
// 	{
// 		while (x++ < fdf ->x_max)
// 		{
// 			x_proj = (x - y) * cos(ANGLE * M_PI / 180);
// 			y_proj = (x + y) * sin(ANGLE * M_PI / 180) - fdf->z[y][x] * Z_SCALE;
// 			if (x_proj > fdf->x_proj_max)
// 				fdf->x_proj_max = x_proj;
// 			if (x_proj < fdf->x_proj_min)
// 				fdf->x_proj_min = x_proj;
// 			if (y_proj > fdf->y_proj_max)
// 				fdf->y_proj_max = y_proj;
// 			if (y_proj < fdf->y_proj_min)
// 				fdf->y_proj_min = y_proj;
// 		}
// 		x = 0;
// 	}
// }

// Bresenham's line algorithm
// void draw_line(int x0, int y0, int x1, int y1, float scale, t_fdf *fdf)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = x0 < x1 ? 1 : -1;
//     int sy = y0 < y1 ? 1 : -1;
//     int err = dx - dy;
//     int e2;

//     while (x0 != x1 || y0 != y1) {
//         img_pix_put(&fdf->img, x0 * scale, y0 * scale, fdf->map_color[y0][x0]);
//         e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }

static void	render_map(t_fdf *fdf)
{
	int	x;
	int	y;
	float	x_proj = 0;
	float	y_proj = 0;

	// float	fdf->x_proj_max;
	// float	fdf->y_proj_max;
	// float	fdf->x_proj_min;
	// float	fdf->y_proj_min;

	fdf->x_proj_max = 0;
	fdf->y_proj_max = 0;
	fdf->x_proj_min = FLT_MAX;
	fdf->y_proj_min = FLT_MAX;

	x = 0;
	y = 0;
	while (y < fdf->y_max)
	{
		while (x < fdf ->x_max)
		{
			x_proj = (x - y) * cos(ANGLE * M_PI / 180);
			y_proj = (x + y) * sin(ANGLE * M_PI / 180) - fdf->z[y][x] * Z_SCALE;
			if (x_proj > fdf->x_proj_max)
				fdf->x_proj_max = x_proj;
			if (x_proj < fdf->x_proj_min)
				fdf->x_proj_min = x_proj;
			if (y_proj > fdf->y_proj_max)
				fdf->y_proj_max = y_proj;
			if (y_proj < fdf->y_proj_min)
				fdf->y_proj_min = y_proj;
			x++;
		}
		x = 0;
		y++;
	}
	printf("fdf->x_proj_max: %.2f\n", fdf->x_proj_max);
	printf("fdf->x_proj_min: %.2f\n", fdf->x_proj_min);
	printf("fdf->y_proj_max: %.2f\n", fdf->y_proj_max);
	printf("fdf->y_proj_min: %.2f\n", fdf->y_proj_min);

	float x_proj_range = fdf->x_proj_max - fdf->x_proj_min;
	float y_proj_range = fdf->y_proj_max - fdf->y_proj_min;

	printf("fdf->x_proj_max: %.2f\n", x_proj_range);
	printf("fdf->y_proj_min: %.2f\n", y_proj_range);

	// Calculate the scale factor to fit the range within the 800x800 window
	float x_scale = (WINDOW_W / (fdf->x_proj_max - fdf->x_proj_min)) * SCREEN_UTIL; // Leaving 10% space on each side
	float y_scale = (WINDOW_H / (fdf->y_proj_max - fdf->y_proj_min)) * SCREEN_UTIL;

	printf("x scale: %.5f\n", x_scale);
	printf("y scale: %.5f\n", y_scale);

	float scale = (x_scale < y_scale) ? x_scale : y_scale;

	printf("scale: %.5f\n", scale);

	x = 0;
	y = 0;
	x_proj = 0;
	y_proj = 0;
	while (y < fdf->y_max)
	{
		while (x < fdf ->x_max)
		{
			x_proj = (((x - y) * cos(ANGLE * M_PI / 180)) - fdf->x_proj_min) * scale + (WINDOW_W - ((fdf->x_proj_max - fdf->x_proj_min) * scale)) / 2;
			y_proj = (((x + y) * sin(ANGLE * M_PI / 180) - fdf->z[y][x] * Z_SCALE) - fdf->y_proj_min) * scale + (WINDOW_H - ((fdf->y_proj_max - fdf->y_proj_min) * scale)) / 2;


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
	render_map(fdf);

	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
