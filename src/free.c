/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/17 15:11:25 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	free_fdf(t_fdf *fdf);
void	free_str_arr(char **array);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// static void	free_int_arr(int **arr, t_fdf *fdf)
// {
// 	int	y;

// 	y = 0;
// 	if (!arr)
// 		return ;
// 	while (y < fdf->map_y)
// 	{
// 		free(arr[y]);
// 		y++;
// 	}
// 	free(arr);
// 	arr = NULL;
// }

void	free_fdf(t_fdf *fdf)
{
	int	y;

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
	if (fdf->map_z)
	{
		y = 0;
		while (y < fdf->map_y)
			free(fdf->map_z[y++]);
		free(fdf->map_z);
		fdf->map_z = NULL;
	}
	if (fdf->map_color)
	{
		y = 0;
		while (y < fdf->map_y)
			free(fdf->map_color[y++]);
		free(fdf->map_color);
		fdf->map_color = NULL;
	}
}

/*
Used in parse_map_z() and parse_map_color().
Frees the memory allocated for an array of strings.
*/
void	free_str_arr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
