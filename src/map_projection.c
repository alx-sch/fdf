/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:03:53 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/22 21:40:49 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions to calculate the appropriate scaling factor and
offsets, ensuring that the projection fits into the image and is centered.
These functions are used to project the 3D coordinates of the map (x, y, z)
into a 2D format for display on the image.
*/

#include "fdf.h"

// IN FILE

void	get_projected_coordinates(t_fdf *fdf);

/*
Used in get_projected_coordinates().
Allocates memory for two 2D matrices to store projected coordinates corresponding
to the map file ('fdf->x_proj' and 'fdf->y_proj').
These matrices hold the projected x and y values on the image for each
map coordinate (x, y, z).
*/
static void	allocate_memory(t_fdf *fdf)
{
	int	y;

	y = 0;
	fdf->x_proj = (float **)ft_calloc(fdf->y_max, sizeof(float *));
	if (!fdf->x_proj)
		perror_and_exit(ERR_MALLOC, fdf);
	fdf->y_proj = (float **)ft_calloc(fdf->y_max, sizeof(float *));
	if (!fdf->y_proj)
		perror_and_exit(ERR_MALLOC, fdf);
	while (y < fdf->y_max)
	{
		fdf->x_proj[y] = (float *)ft_calloc(fdf->x_max, sizeof(float));
		if (!fdf->x_proj[y])
			perror_and_exit(ERR_MALLOC, fdf);
		fdf->y_proj[y] = (float *)ft_calloc(fdf->x_max, sizeof(float));
		if (!fdf->y_proj[y])
			perror_and_exit(ERR_MALLOC, fdf);
		y++;
	}
}

/*
Used in get_scale().
Projects the map's coordinates (3D: x, y, z) into a 2D projection with the
specified 'ANGLE' between the horizontal line and the x and y axes.
These projected coordinates might be negative or larger than the image
width/height would allow, potentially causing a segmentation fault when trying
to access out-of-bounds locations in the image buffer (see img_pix_put()).
To prevent this, the minimum and maximum values of the projected x and y
coordinates are stored in the 'fdf' structure for use in determining
the scaling factor and offsets.
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
Used in get_projected_coordinates().
Calculates the scaling factor required to fit the projected map within the
image. Stores the smaller of the two scaling factors in 'fdf->scale', ensuring
that the entire map fits within the window.
*/
static void	get_scale(t_fdf *fdf)
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
Used in get_projected_coordinates().
Calculates and stores the offset from the window's x and y coordinates necessary
to center the projection in 'fdf->x_offset' and 'fdf->y_offset'.
*/
static void	get_offset(t_fdf *fdf)
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

/*
Projects the x, y, and z coordinates of the map into a 2D format, allowing
the drawing of the projection onto the image.
Projected coordinates are stored in matrices 'fdf->x_proj' and 'fdf->y_proj'.
*/
void	get_projected_coordinates(t_fdf *fdf)
{
	int		x;
	int		y;
	float	x_proj;
	float	y_proj;

	x = 0;
	y = 0;
	get_scale(fdf);
	get_offset(fdf);
	allocate_memory(fdf);
	while (y < fdf->y_max)
	{
		while (x < fdf ->x_max)
		{
			x_proj = (((x - y) * cos(ANGLE * M_PI / 180)) - fdf->x_proj_min)
				* fdf->scale + fdf->x_offset;
			y_proj = (((x + y) * sin(ANGLE * M_PI / 180) - fdf->z[y][x] * Z_S)
					- fdf->y_proj_min) * fdf->scale + fdf->y_offset;
			fdf->x_proj[y][x] = x_proj;
			fdf->y_proj[y][x] = y_proj;
			x++;
		}
		x = 0;
		y++;
	}
}
