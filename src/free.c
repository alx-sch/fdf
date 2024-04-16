/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/16 20:42:02 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	free_fdf(t_fdf *fdf);
void	free_arr(char **array);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

void	free_fdf(t_fdf *fdf)
{
	int	y;

	if (!fdf)
		return ;
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
	if (fdf->mlx)
		free(fdf->mlx);
}

/*
Used in parse_map_z() and parse_map_color().
Frees the memory allocated for an array of strings.
*/
void	free_arr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
