/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:12:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/17 12:57:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to parse the color values as integers to
'fdf->map_color'. If no color codes are provided for an entry, the default
WIRE_COLOR is used.
*/

#include "fdf.h"

void	get_map_color(t_fdf *fdf, char *file);

/*
Used in parse_map_color().
Parses a hexadecimal color code string and validates its format and range
(FFFFFF == 16777215);
Returns:
 - The integer representation of the color code via ft_atoi_base(), if valid.
 - Otherwise, frees allocated memory, prints error message and terminates
   the program.
*/
static int	get_color_code(char *color_str, char **token_arr, t_fdf *fdf)
{
	int	color_int;

	if (ft_strncmp(color_str + 1, "0x", 2) == 0
		|| ft_strncmp(color_str + 1, "0X", 2) == 0)
	{
		color_int = ft_atoi_base(color_str + 3, 16);
		if (color_int >= 0 && color_int <= 16777215)
			return (color_int);
	}
	free_str_arr(token_arr);
	free_fdf(fdf);
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/*
Used in get_map_color().
If your color information is consistently provided in a format like 0xRRGGBB,
you can directly parse it as an integer without extracting it as a string.
*/
static void	parse_map_color(t_fdf *fdf, int y)
{
	int		x;
	char	*color_str;
	char	**token_arr;

	x = 0;
	token_arr = ft_split(fdf->line, ' ');
	if (!token_arr)
		perror_and_exit(ERR_SPLIT, fdf);
	while (x < fdf->map_x)
	{
		color_str = ft_strchr(token_arr[x], ',');
		if (color_str)
		{
			fdf->color_provided = 1;
			fdf->map_color[y][x] = get_color_code(color_str, token_arr, fdf);
		}
		else
			fdf->map_color[y][x] = WIRE_COLOR;
		x++;
	}
	free_str_arr(token_arr);
}

/*
Parses the color values of the map into the fdf structure.
If no color code is provided for an entry, the default 'WIRE_COLOR' is used.
The function allocates memory, reads and checks the values color codes,
and stores them in the int matrix 'fdf->map_color'.
*/
void	get_map_color(t_fdf *fdf, char *file)
{
	int		y;

	y = 0;
	fdf->map_color = (int **)ft_calloc(fdf->map_y, sizeof(int *));
	if (!fdf->map_color)
		perror_and_exit(ERR_MALLOC, fdf);
	fdf->fd = open(file, O_RDONLY);
	if (-1 == fdf->fd)
		perror_and_exit(file, fdf);
	fdf->line = get_next_line(fdf->fd);
	while (fdf->line != NULL)
	{
		fdf->map_color[y] = (int *)ft_calloc(fdf->map_x, sizeof(int));
		if (!fdf->map_color[y])
			perror_and_exit(ERR_MALLOC, fdf);
		parse_map_color(fdf, y);
		free(fdf->line);
		fdf->line = get_next_line(fdf->fd);
		y++;
	}
	close(fdf->fd);
}
