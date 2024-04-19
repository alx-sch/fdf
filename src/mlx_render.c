/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/19 18:22:29 by aschenk          ###   ########.fr       */
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
	float	x_trans = 0;
	float	y_trans = 0;
	float 	x_trans_max = 0;
	float 	y_trans_max = 0;
	float 	x_trans_min = FLT_MAX;
	float 	y_trans_min = FLT_MAX;
	float	z_scale = 0.1;

	x = 0;
	y = 0;
	while (y < fdf->map_y)
	{
		while (x < fdf ->map_x)
		{
			x_trans = (x - y) * cos(ANGLE * M_PI / 180);
			y_trans = (x + y) * sin(ANGLE * M_PI / 180) - fdf->map_z[y][x] * z_scale;
			if (x_trans > x_trans_max)
				x_trans_max = x_trans;
			if (x_trans < x_trans_min)
				x_trans_min = x_trans;
			if (y_trans > y_trans_max)
				y_trans_max = y_trans;
			if (y_trans < y_trans_min)
				y_trans_min = y_trans;
			x++;
		}
		x = 0;
		y++;
	}
	// printf("x_trans_max: %.2f\n", x_trans_max);
	// printf("x_trans_min: %.2f\n", x_trans_min);
	// printf("y_trans_max: %.2f\n", y_trans_max);
	// printf("y_trans_min: %.2f\n", y_trans_min);

// 	float x_trans_range = x_trans_max - x_trans_min;
// 	float y_trans_range = y_trans_max - y_trans_min;

// // Calculate the width and height of the range
// 	float x_width = x_trans_range;
// 	float y_height = y_trans_range;

// 	// Calculate the scale factor to fit the range within the 800x800 window
// 	float x_scale = 800.0 / (x_width * 1.1); // Leaving 10% space on each side
// 	float y_scale = 800.0 / (y_height * 1.1);

// 	float scale = (x_scale > y_scale) ? x_scale : y_scale;

// 	printf("scale: %.5f\n", scale);

	x = 0;
	y = 0;
	x_trans = 0;
	y_trans = 0;
	while (y < fdf->map_y)
	{
		while (x < fdf ->map_x)
		{
			x_trans = (((x - y) * cos(ANGLE * M_PI / 180)) - x_trans_min);
			y_trans = (((x + y) * sin(ANGLE * M_PI / 180) - fdf->map_z[y][x] * z_scale) - y_trans_min);
			img_pix_put(&fdf->img, x_trans, y_trans, fdf->map_color[y][x]);
			// printf("x_trans %d: %.2f\n", x, x_trans);
			// printf("y_trans %d: %.2f\n", y, y_trans);
			x++;
		}
		x = 0;
		y++;
	}
}

static int	handle_events(t_fdf *fdf)
{
	if (fdf->close_window)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
		mlx_loop_end(fdf->mlx);
	}
	return (0);
}


// DestryNotify: 'x' in window is clicked
void	render_image(t_fdf *fdf)
{
	render_background(fdf);
	render_map(fdf);

	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);

	mlx_hook(fdf->win, DestroyNotify, 0, &close_window, fdf);
	mlx_hook(fdf->win, KeyPress, KeyPressMask, &handle_keypress, fdf);
	mlx_loop_hook(fdf->mlx, &handle_events, fdf);
	mlx_loop(fdf->mlx);
}
