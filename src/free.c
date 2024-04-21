/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/21 23:30:45 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	free_fdf(t_fdf **fdf_ptr);
void	free_str_arr(char ***array_ptr);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Used in free_fdf().
Frees the memory allocated for a matrix of int values
and sets all pointers to NULL.
*/
static void	free_int_arr(int ***array_ptr, t_fdf *fdf)
{
	int	y;
	int	**array;

	y = 0;
	array = *array_ptr;
	if (!array)
		return ;
	while (y < fdf->y_max)
	{
		free(array[y]);
		y++;
	}
	free(array);
	*array_ptr = NULL;
}

/*
Used in free_fdf().
Frees all resources associated with the mlx components and set all pointers
to NULL for the window, image, and display (connection to X11).
*/
static void	free_mlx(t_fdf *fdf)
{
	if (fdf->mlx)
	{
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		if (fdf->img.img)
			mlx_destroy_image(fdf->mlx, fdf->img.img);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		fdf->win = NULL;
		fdf->img.img = NULL;
		fdf->img.data = NULL;
		fdf->mlx = NULL;
	}
}

/*
Frees/closes all resources allocated for the fdf structure, including
mlx-related ressources, file descriptor, memory for line reading and matrices
of int values for map z and colors.
get_next_line(-1) is called to free the static 'stash' used between gnl calls
(which is necessary if file was not read until EOF).
*/
void	free_fdf(t_fdf **fdf_ptr)
{
	t_fdf	*fdf;

	fdf = *fdf_ptr;
	if (!fdf)
		return ;
	free_mlx(fdf);
	close (fdf->fd);
	if (fdf->line)
	{
		get_next_line(-1);
		free(fdf->line);
	}
	free_int_arr(&fdf->z, fdf);
	free_int_arr(&fdf->color, fdf);
	*fdf_ptr = NULL;
}

/*
Used in parse_map_z() and parse_map_color().
Frees the memory allocated for a matrix of strings
and sets all pointers to NULL.
*/
void	free_str_arr(char ***array_ptr)
{
	int		i;
	char	**array;

	i = 0;
	array = *array_ptr;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	*array_ptr = NULL;
}
