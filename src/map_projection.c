/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:03:53 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/22 20:35:14 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions to calculate the appropriate scaling factor and
offsets, ensuring that the projection fits into the window and is centered.
*/

#include "fdf.h"

// IN FILE

/*
Allocates memory for two 2D arrays ('fdf->x_proj' and 'fdf->y_proj') to store
projected coordinates corresponding to the map file.
These arrays hold the projected x and y values on the screen for each
map coordinate (x, y, z).
*/
// static void	allocate_memory(t_fdf *fdf)
// {
// 	int	y;

// 	y = 0;
// 	fdf->x_proj = (float **)ft_calloc(fdf->y_max, sizeof(float));
// 	if (!fdf->x_proj)
// 		perror_and_exit(ERR_MALLOC, fdf);
// 	fdf->y_proj = (float **)ft_calloc(fdf->y_max, sizeof(float));
// 	if (!fdf->y_proj)
// 		perror_and_exit(ERR_MALLOC, fdf);
// 	while (y < fdf->y_max)
// 	{
// 		fdf->x_proj[y] = (float *)ft_calloc(fdf->x_max, sizeof(float));
// 		if (!fdf->x_proj[y])
// 			perror_and_exit(ERR_MALLOC, fdf);
// 		fdf->y_proj[y] = (float *)ft_calloc(fdf->x_max, sizeof(float));
// 		if (!fdf->y_proj[y])
// 			perror_and_exit(ERR_MALLOC, fdf);
// 		y++;
// 	}
// }

/*
Used in get_scale().
Projects the map's coordinates (3D: x, y, z) into 2D projection (x_proj, y_proj)
with a specified 'ANGLE' between the horizontal line and x and y axis.
These projected coordinates might be negative or larger than the
image width/height would allow, creating a segmentation fault when trying to
access these out-of-bounds locations in the image buffer (see img_pix_put()).
In order to avoid this, the min. and max. values of the projected x and y
coordinates are stroed in the 'fdf' structure and other fcts to determine the
scaling factor and offsets.
*/
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
		while (++x < fdf->x_max)
		{
			printf("x: %d\n", x);
			x_proj = (x - y) * cos(ANGLE * M_PI / 180);
			y_proj = (x + y) * sin(ANGLE * M_PI / 180) - fdf->z[y][x] * Z_S;
			if (x_proj > fdf->x_proj_max)
				fdf->x_proj_max = x_proj;
			if (x_proj < fdf->x_proj_min)
				fdf->x_proj_min = x_proj;
			if (y_proj > fdf->y_proj_max)
				fdf->y_proj_max = y_proj;
			if (y_proj < fdf->y_proj_min)
				fdf->y_proj_min = y_proj;
		}
		x = -1;
	}
}

/*
Calculates the scaling factor needed to fit the projected map within the window.
The smaller of the two scaling factors is stored in 'fdf->scale', ensuring that
the entire map fits within the window.
*/
void	get_scale(t_fdf *fdf)
{
	float	x_range;
	float	y_range;
	float	x_scale;
	float	y_scale;
	float	scale;

	get_extrema(fdf);
	x_range = fdf->x_proj_max - fdf->x_proj_min;
	y_range = fdf->y_proj_max - fdf->y_proj_min;
	x_scale = WINDOW_W / x_range * SCREEN_UTIL;
	y_scale = WINDOW_H / y_range * SCREEN_UTIL;
	if (x_scale < y_scale)
		scale = x_scale;
	else
		scale = y_scale;
	fdf->scale = scale;
}

/*
Saves the offset from window's x and y needed to center the projection
in 'fdf->x_offset' and 'fdf->y_offset', respectively.
*/
void	get_offset(t_fdf *fdf)
{
	float	x_range;
	float	y_range;
	float	x_offset;
	float	y_offset;

	x_range = fdf->x_proj_max - fdf->x_proj_min;
	y_range = fdf->y_proj_max - fdf->y_proj_min;
	x_offset = (WINDOW_W - (x_range * fdf->scale)) / 2;
	fdf->x_offset = x_offset;
	y_offset = (WINDOW_H - (y_range * fdf->scale)) / 2;
	fdf->y_offset = y_offset;
}
