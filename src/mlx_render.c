/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:37:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/16 20:13:47 by aschenk          ###   ########.fr       */
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

static int	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		i++;
	}
	return (0);
}

static void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_H)
	{
		j = 0;
		while (j < WINDOW_W)
			img_pix_put(img, j++, i, color);
		i++;
	}
}


static int	render(t_fdf *fdf)
{
	if (!fdf->win)
		return (1);
	render_background(&fdf->img, BG_COLOR);
	render_rect(&fdf->img, (t_rect){WINDOW_W - 100, WINDOW_H - 100, 100, 100,
		BLACK});
	render_rect(&fdf->img, (t_rect){0, 0, 100, 100, RED});
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}

void	render_image(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &render, fdf);

	mlx_hook(fdf->win, KeyPress, KeyPressMask, &handle_keypress, fdf);
	mlx_hook(fdf->win, DestroyNotify, 0, &close_window, fdf); // 'x' in window is clicked

	mlx_loop(fdf->mlx);

}
