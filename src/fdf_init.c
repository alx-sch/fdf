/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 00:02:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE
void	init_fdf(t_fdf *fdf, char *file);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Initializing pointers in fdf structure to NULL.
This helps to avoid having them dangling when being used, like in free_fdf()
which is called when unexpected errors occur.
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
