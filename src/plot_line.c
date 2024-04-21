/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:27:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/21 23:53:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*Initialize in the structure pointed at by 'ut' the initial values needed by
the Bresenham algorithm:
• (x0, y0) coordinates of the starting point
• (x1, y1) coordinates of the ending point
• delta_x: the absolute difference between x1 and x0
• delta_y: the absolute difference between y1 and y0
• is_steep: boolean indicating a steep line, based on delta_x and delta_y
• step_x: the direction in which to increase x in the algorithm
• step_y: the direction in which to increase y in the algorithm
• Call to the second part of the init function, init_bresenham_utils_2*/
// void	init_bresenham_utils(t_br_utils *ut, t_fdf *fdf)
// {
// 	ut->x0 = (int)a.x;
// 	ut->y0 = (int)a.y;
// 	ut->x1 = (int)b.x;
// 	ut->y1 = (int)b.y;
// 	ut->delta_x = abs(ut->x1 - ut->x0);
// 	ut->delta_y = abs(ut->y1 - ut->y0);
// 	ut->err = ut->delta_x - ut->delta_y;
// 	if (ut->x1 >= ut->x0)
// 		ut->step_x = 1;
// 	else
// 		ut->step_x = -1;
// 	if (ut->y1 >= ut->y0)
// 		ut->step_y = 1;
// 	else
// 		ut->step_y = -1;
// }

// // /*Draws a line in the image pointed at by 'img', with colour 'colour' from
// // starting point (a.x, a.y) to ending point (b.x, b.y)*/
// void	plot(t_vect_3 a, t_vect_3 b, mlx_image_t *img, int colour)
// {
// 	t_br_utils	ut;

// 	init_bresenham_utils(&ut, a, b);
// 	while (ut.x0 != ut.x1 || ut.y0 != ut.y1)
// 	{
// 		if (ut.x0 >= 0 && ut.x0 <= WIDTH && ut.y0 >= 0 && ut.y0 <= HEIGTH)
// 			mlx_put_pixel(img, ut.x0, ut.y0, colour);
// 		ut.e2 = 2 * ut.err;
// 		if (ut.e2 > -ut.delta_y)
// 		{
// 			ut.err -= ut.delta_y;
// 			ut.x0 += ut.step_x;
// 		}
// 		if (ut.e2 < ut.delta_x)
// 		{
// 			ut.err += ut.delta_x;
// 			ut.y0 += ut.step_y;
// 		}
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

static void	get_extrema(t_fdf *fdf)
{
	int	x;
	int	y;
	int	x_proj;
	int	y_proj;

	x = -1;
	y = -1;
	while (++y < fdf->y_max)
	{
		while (++x < fdf ->x_max)
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
		}
		x = 0;
	}
}