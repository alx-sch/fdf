/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/17 19:06:59 by aschenk          ###   ########.fr       */
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

	pixel = img->data + (y * img->size_len + x * (img->bpp / 8));
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

static void	render_map(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < fdf->map_y)
	{
		while (x < fdf ->map_x)
		{
			img_pix_put(&fdf->img, x, y, fdf->map_color[y][x]);
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
