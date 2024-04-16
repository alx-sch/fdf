/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_z.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:39:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/16 19:42:45 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to parse the z-values (map depth) to 'fdf->map_z'.
*/

#include "fdf.h"

void	get_map_z(t_fdf *fdf, char *file);

/*
Helper function for get_map_z().
Parses z-values from the passed string ('line') into 'fdf->map_z'.
Utilizes ft_split() to tokenize the line and converts each token into an integer
using ft_atoi(), effectively filtering out additional information, e.g. color.
*/
static	void	parse_map_z(t_fdf *fdf, int y)
{
	int		x;
	char	**token_arr;

	x = 0;
	token_arr = ft_split(fdf->line, ' ');
	if (!token_arr)
		perror_and_exit(ERR_SPLIT, fdf);
	while (x < fdf->map_x)
	{
		fdf->map_z[y][x] = ft_atoi(token_arr[x]);
		x++;
	}
	free_arr(token_arr);
}

/*
Parses the z-values of the map into the fdf structure.
The function allocates memory, reads the values from the map,
parses them via ft_atoi(), and stores them in the int matrix 'fdf->map_z'.
*/
void	get_map_z(t_fdf *fdf, char *file)
{
	int	y;

	y = 0;
	fdf->map_z = (int **)ft_calloc(fdf->map_y, sizeof(int *));
	if (!fdf->map_z)
		perror_and_exit(ERR_MALLOC, fdf);
	fdf->fd = open(file, O_RDONLY);
	if (-1 == fdf->fd)
		perror_and_exit(file, fdf);
	fdf->line = get_next_line(fdf->fd);
	while (fdf->line != NULL)
	{
		fdf->map_z[y] = (int *)ft_calloc(fdf->map_x, sizeof(int));
		if (!fdf->map_z[y])
			perror_and_exit(ERR_MALLOC, fdf);
		parse_map_z(fdf, y);
		free(fdf->line);
		fdf->line = get_next_line(fdf->fd);
		y++;
	}
	close(fdf->fd);
}
