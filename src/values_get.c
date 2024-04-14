/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:39:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 01:05:15 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	get_map_z(t_fdf *fdf, char *file);
void	get_map_color(t_fdf *fdf, char *file);

/*
Used in parse_map_z() and parse_map_color().
Frees the memory allocated for an array of strings.
*/
static void	free_arr(char **array)
{
	size_t	i;

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

/*
Helper function for get_map_z().
Parses z-values from the passed string ('line') into 'fdf->map_z'.
Utilizes ft_split() to tokenize the line and converts each token into an integer
using ft_atoi(), effectively filtering out additional color information.
*/
static	void	parse_map_z(t_fdf *fdf, int row, char *line)
{
	int		col;
	char	**token_arr;

	col = 0;
	token_arr = ft_split(line, ' ');
	if (!token_arr)
		perror_and_exit(ERR_SPLIT, fdf);
	while (col < fdf->map_x)
	{
		fdf->map_z[row][col] = ft_atoi(token_arr[col]);
		col++;
	}
	free_arr(token_arr);
}

/*
Parses the z-values of the map from a file into the fdf structure
(int **fdf->map.z).
The function allocates memory, reads the values from the file,
parses them via ft_atoi(), and stores them in the int array.
*/
void	get_map_z(t_fdf *fdf, char *file)
{
	int		row;
	int		fd;
	char	*line;

	fdf->map_z = (int **)ft_calloc(fdf->map_y, sizeof(int *));
	if (!fdf->map_z)
		perror_and_exit(ERR_MALLOC, fdf);
	fd = open(file, O_RDONLY);
	if (-1 == fd)
		perror_and_exit(file, fdf);
	row = 0;
	while (row < fdf->map_y)
	{
		fdf->map_z[row] = (int *)ft_calloc(fdf->map_x, sizeof(int));
		if (!fdf->map_z[row])
			perror_and_exit(ERR_MALLOC, fdf);
		line = get_next_line(fd);
		if (!line)
			perror_and_exit(ERR_GNL, fdf);
		parse_map_z(fdf, row, line);
		free(line);
		row++;
	}
	close(fd);
}

/*
Helper function for get_map_color().
*/
static void	parse_map_color(t_fdf *fdf, int row, char *line)
{
	int		col;
	char	*color_str;
	char	**token_arr;

	col = 0;
	color_str = NULL;
	token_arr = ft_split(line, ' ');
	if (!token_arr)
		perror_and_exit(ERR_SPLIT, fdf);
	while (col < fdf->map_x)
	{
		color_str = ft_strchr(token_arr[col], ',');
		if (color_str)
		{
			fdf->color_provided = 1;
			ft_printf("row: %d, col: %d, color: %s\n", row, col, color_str + 1);
		}
		else
			ft_printf("row: %d, col: %d, color: %d\n", row, col, WIRE_COLOR);
		col++;
	}
	free_arr(token_arr);
}

void	get_map_color(t_fdf *fdf, char *file)
{
	int		row;
	int		fd;
	char	*line;

	fdf->map_color = (int **)ft_calloc(fdf->map_y, sizeof(int *));
	if (!fdf->map_color)
		perror_and_exit(ERR_MALLOC, fdf);
	fd = open(file, O_RDONLY);
	if (-1 == fd)
		perror_and_exit(file, fdf);
	row = 0;
	while (row < fdf->map_y)
	{
		fdf->map_color[row] = (int *)ft_calloc(fdf->map_x, sizeof(int));
		if (!fdf->map_color[row])
			perror_and_exit(ERR_MALLOC, fdf);
		line = get_next_line(fd);
		if (!line)
			perror_and_exit(ERR_GNL, fdf);
		parse_map_color(fdf, row, line);
		free(line);
		row++;
	}
	close(fd);
	get_next_line(-1);
}
