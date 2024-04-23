/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/23 16:47:42 by aschenk          ###   ########.fr       */
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

// void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (x0 != x1 || y0 != y1)
	{
        img_pix_put(img, x0, y0, color);
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
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

	for (int y = 0; y < fdf->y_max; y++) {
        for (int x = 0; x < fdf->x_max; x++) {
            if (x < (fdf->x_max - 1))
                draw_line(&fdf->img, fdf->x_proj[y][x], fdf->y_proj[y][x], fdf->x_proj[y][x + 1],  fdf->y_proj[y][x+1], fdf->color[y][x]); // Draw horizontal line
            if (y < (fdf->y_max -1))
                draw_line(&fdf->img, fdf->x_proj[y][x],  fdf->y_proj[y][x], fdf->x_proj[y + 1][x], fdf->y_proj[y +1][x], fdf->color[y][x]); // Draw vertical line
        }
    }
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
