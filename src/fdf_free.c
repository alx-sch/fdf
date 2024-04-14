/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:20:11 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/14 22:57:59 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
