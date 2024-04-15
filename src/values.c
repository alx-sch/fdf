/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:39:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 19:19:00 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	get_map_z(t_fdf *fdf, char *file);
void	get_map_color(t_fdf *fdf, char *file);

/*
Helper function for get_map_z().
Parses z-values from the passed string ('line') into 'fdf->map_z'.
Utilizes ft_split() to tokenize the line and converts each token into an integer
using ft_atoi(), effectively filtering out additional information, e.g. color.
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
parses them via ft_atoi(), and stores them in an int matrix.
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
Used in parse_map_color().
Parses a hexadecimal color code string and validates its format and range.
Returns:
 - The integer representation of the color code if valid.
 - Otherwise, frees allocated memory, prints error message and terminates
   the program.
*/
static int	check_and_parse_color_code(char *color_str, char *line,
	char **token_arr, t_fdf *fdf)
{
	int	color_int;

	if (ft_strncmp(color_str + 1, "0x", 2) == 0
		|| ft_strncmp(color_str + 1, "0X", 2) == 0)
	{
		color_int = ft_atoi_base(color_str + 3, 16);
		if (color_int >= 0 && color_int <= 16777215)
			return (color_int);
	}
	free(line);
	free_arr(token_arr);
	get_next_line(-1);
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	free_fdf(fdf);
	exit(EXIT_FAILURE);
}

/*
Used in get_map_color().
If your color information is consistently provided in a format like 0xRRGGBB,
 you can directly parse it as an integer without extracting it as a string.
*/
static void	parse_map_color(t_fdf *fdf, int row, char *line)
{
	int		column;
	char	*color_str;
	char	**token_arr;

	column = 0;
	color_str = NULL;
	token_arr = ft_split(line, ' ');
	if (!token_arr)
		perror_and_exit(ERR_SPLIT, fdf);
	while (column < fdf->map_x)
	{
		color_str = ft_strchr(token_arr[column], ',');
		if (color_str)
		{
			fdf->color_provided = 1;
			fdf->map_color[row][column] = check_and_parse_color_code(
					color_str, line, token_arr, fdf);
		}
		else
			fdf->map_color[row][column] = WIRE_COLOR;
		column++;
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
