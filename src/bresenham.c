/*
This file contains functions to initialize a Bresenham line drawing algorithm
for either a horizontal or vertical line segment in a 2D grid. The functions
populate the respective parameters into a data structure.
*/

#include "fdf.h"

// IN FILE:

void	init_bresenham_horz(t_bresenham *bresen, t_fdf *fdf, int row, int col);
void	init_bresenham_vert(t_bresenham *bresen, t_fdf *fdf, int row, int col);

/*
Initializes Bresenham parameters for drawing a horizontal line segment
(along the map width).
Populates the parameters of the t_bresenham structure with the coordinates and
differences necessary for the Bresenham's line drawing algorithm.

Parameters:
- bresen: A pointer to a t_bresenham struct where the parameters will be stored.
- fdf: A pointer to a t_fdf structure containing the 2D grid and projection data.
- row: The row index of the starting point of the line segment (map height).
- col: The column index of the starting point of the line segment (map width).

See definition of 't_bresenham' for a detailed parameter description.
*/
void	init_bresenham_horz(t_bresenham *bresen, t_fdf *fdf, int row, int col)
{
	bresen->x0 = (int)fdf->x_proj[row][col];
	bresen->y0 = (int)fdf->y_proj[row][col];
	bresen->x1 = (int)fdf->x_proj[row][col + 1];
	bresen->y1 = (int)fdf->y_proj[row][col + 1];
	if ((bresen->x1 - bresen->x0) >= 0)
		bresen->dx = bresen->x1 - bresen->x0 ;
	else
		bresen->dx = bresen->x0 - bresen->x1;
	if ((bresen->y1 - bresen->y0) >= 0)
		bresen->dy = bresen->y1 - bresen->y0 ;
	else
		bresen->dy = bresen->y0 - bresen->y1;
	if (bresen->x0 < bresen->x1)
		bresen->sx = 1;
	else
		bresen->sx = -1;
	if (bresen->y0 < bresen->y1)
		bresen->sy = 1;
	else
		bresen->sy = -1;
}

/*
Initializes Bresenham parameters for drawing a vertical line segment
(along the map height).
Populates the parameters of the t_bresenham structure with the coordinates
and differences necessary for the Bresenham's line drawing algorithm.

Parameters:
- bresen: A pointer to a t_bresenham struct where the parameters will be stored.
- fdf: A pointer to a t_fdf structure containing the 2D grid and projection data.
- row: The row index of the starting point of the line segment (map height).
- col: The column index of the starting point of the line segment (map width).

See definition of 't_bresenham' for a detailed parameter description.
*/
void	init_bresenham_vert(t_bresenham *bresen, t_fdf *fdf, int row, int col)
{
	bresen->x0 = (int)fdf->x_proj[row][col];
	bresen->y0 = (int)fdf->y_proj[row][col];
	bresen->x1 = (int)fdf->x_proj[row + 1][col];
	bresen->y1 = (int)fdf->y_proj[row + 1][col];
	if ((bresen->x1 - bresen->x0) >= 0)
		bresen->dx = bresen->x1 - bresen->x0;
	else
		bresen->dx = bresen->x0 - bresen->x1;
	if ((bresen->y1 - bresen->y0) >= 0)
		bresen->dy = bresen->y1 - bresen->y0 ;
	else
		bresen->dy = bresen->y0 - bresen->y1;
	if (bresen->x0 < bresen->x1)
		bresen->sx = 1;
	else
		bresen->sx = -1;
	if (bresen->y0 < bresen->y1)
		bresen->sy = 1;
	else
		bresen->sy = -1;
}
