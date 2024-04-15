/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 19:05:50 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE
void	init_fdf(t_fdf *fdf, char *file);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Initializing pointers in the fdf structure to NULL.
This helps to avoid having them dangling when being used, e.g. in free_fdf(),
which is called whenever unexpected errors occur.
*/
static void	null_fdf(t_fdf *fdf)
{
	fdf->mlx = NULL;
	fdf->win = NULL;
	fdf->map_z = NULL;
	fdf->map_color = NULL;
	fdf->color_provided = 0;
}


void	init_fdf(t_fdf *fdf, char *file)
{
	null_fdf(fdf);
	fdf->map_y = check_and_get_map_y(file);
	fdf->map_x = check_and_get_map_x(file);
	get_map_z(fdf, file);
	get_map_color(fdf, file);
}

void	free_fdf(t_fdf *fdf)
{
	int	i;

	if (!fdf)
		return ;
	if (fdf->map_z)
	{
		i = 0;
		while (i < fdf->map_y)
			free(fdf->map_z[i++]);
		free(fdf->map_z);
		fdf->map_z = NULL;
	}
	if (fdf->map_color)
	{
		i = 0;
		while (i < fdf->map_y)
			free(fdf->map_color[i++]);
		free(fdf->map_color);
		fdf->map_color = NULL;
	}
}
