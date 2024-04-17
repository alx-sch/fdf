/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/17 16:56:45 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	free_fdf(t_fdf *fdf);
void	free_str_arr(char ***array);

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
	while (y < fdf->map_y)
	{
		free(array[y]);
		y++;
	}
	free(array);
	*array_ptr = NULL;
}

/*
Frees/closes all ressources allocated for the fdf structure, including
mlx-related ressources, file descriptor, memory for line reading and matrices
of int values for map z and colors.
*/
void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (fdf->mlx)
	{
		if (fdf->img.img)
			mlx_destroy_image(fdf->mlx, fdf->img.img);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	close (fdf->fd);
	if (fdf->line)
	{
		get_next_line(-1);
		free(fdf->line);
	}
	free_int_arr(&fdf->map_z, fdf);
	free_int_arr(&fdf->map_color, fdf);
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
