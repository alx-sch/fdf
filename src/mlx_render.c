/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/18 17:59:36 by aschenk          ###   ########.fr       */
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
	float	iso_x;
	float	iso_y;
	// float	z_offset;
	float	scale = 30;
	int	angle = 45;
	float	z_scale = 1.4;

	x = 0;
	y = 0;
	while (y < fdf->map_y)
	{
		while (x < fdf ->map_x)
		{
			iso_x = (x - y) * cos(angle * M_PI / 180); // 45 degrees in radians
			iso_y = (x + y) * sin(angle * M_PI / 180); // 45 degrees in radians
			iso_x += WINDOW_W / (scale * 2.3);
			iso_y += WINDOW_H / (scale * 5);
			float z_offset = fdf->map_z[y][x] * z_scale;
			img_pix_put(&fdf->img, (iso_x) * scale, iso_y * scale -z_offset, fdf->map_color[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}

static int	render(t_fdf *fdf)
{
	render_background(fdf);
	render_map(fdf);


	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);

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
	mlx_loop_hook(fdf->mlx, &render, fdf);

	mlx_hook(fdf->win, DestroyNotify, 0, &close_window, fdf);
	mlx_hook(fdf->win, KeyPress, KeyPressMask, &handle_keypress, fdf);

	mlx_loop(fdf->mlx);

}
