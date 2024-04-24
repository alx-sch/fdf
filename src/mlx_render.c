/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/24 21:12:11 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions to render a 3D map grid in a 2D image using
Bresenham's line drawing algorithm.
*/

#include "fdf.h"

void	render_map_grid(t_fdf *fdf);

/*
Used as a more performative alternative to of mlx_pixel_put().
Source: https://harm-smits.github.io/42docs/libs/minilibx.

Sets the color of a pixel at a specified position within the image buffer.
Calculates the memory location (pixel) where the color value will be stored
in the image buffer. The function then assigns the color value at that
buffer location.


Imagine the image buffer to be a 1D array:
- y * img->size_len:	Calculates the starting index of the pixel row within
						the image buffer.
- x * img->bpp / 8:		Calculates the offset within the pixel row to access
						the beginning of a specific pixel. 'img->bpp / 8'
						calculates the number of bytes per pixel.
- *(int *)pixel:	The color is stored as an integer (4 bytes), representing
					RGB (3 bytes). While there is also enough space for ARGB
					(4 bytes), it appears that the alpha channel is not
					being utilized: Same output for 0xFFFF0000, 0x00FF0000.

*/
static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + (y * img->size_len + x * img->bpp / 8);
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

/*
Draws a line segment on the image using Bresenham's line drawing algorithm
in the indicated direction (horizontal, along the map width, or vertical,
along the map height).

Initializes a t_bresenham structure based on the specified direction
and starting coordinates. It then uses Bresenham's line drawing algorithm to
plot points along the line segment on the image. The color of each pixel is
determined by the color specified in the fdf structure.
*/
static void	draw_line(t_fdf *fdf, int row, int col, char *direction)
{
	t_bresenham	bresen;
	int			err;
	int			e2;

	if (ft_strcmp(direction, "horizontal") == 0)
		init_bresenham_horz(&bresen, fdf, row, col);
	else
		init_bresenham_vert(&bresen, fdf, row, col);
	err = bresen.dx - bresen.dy;
	while (bresen.x0 != bresen.x1 || bresen.y0 != bresen.y1)
	{
		img_pix_put(&fdf->img, bresen.x0, bresen.y0, fdf->color[row][col]);
		e2 = 2 * err;
		if (e2 > -bresen.dy)
		{
			err -= bresen.dy;
			bresen.x0 += bresen.sx;
		}
		if (e2 < bresen.dx)
		{
			err += bresen.dx;
			bresen.y0 += bresen.sy;
		}
	}
}

/*
Renders the map grid onto the image and displays in in the window.
- Renders the background.
- Iterates over each map row and column, drawing line segments between them.
- Finally, displays the rendered image on the window.
*/
void	render_map_grid(t_fdf *fdf)
{
	int	row;
	int	col;

	render_background(fdf);
	row = 0;
	while (row < fdf->y_max)
	{
		col = 0;
		while (col < fdf->x_max)
		{
			if (col < (fdf->x_max - 1))
				draw_line(fdf, row, col, "horizontal");
			if (row < (fdf->y_max -1))
				draw_line(fdf, row, col, "vertical");
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
