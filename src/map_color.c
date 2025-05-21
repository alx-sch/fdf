/*
This file contains a function to parse the color values as integers to
int matrix 'fdf->color'. If no color codes are provided for an entry, the default
WIRE_COLOR is used.
*/

#include "fdf.h"

// IN FILE:

void	get_color(t_fdf *fdf, char *file);

/*
Used in parse_color().
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
	free_str_arr(&token_arr);
	free_fdf(&fdf);
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/*
Used in get_color().
If your color information is consistently provided in a format like 0xRRGGBB,
you can directly parse it as an integer without extracting it as a string.
*/
static void	parse_color(t_fdf *fdf, int y)
{
	int		x;
	char	*color_str;
	char	**token_arr;

	x = 0;
	token_arr = ft_split(fdf->line, ' ');
	if (!token_arr)
		perror_and_exit(ERR_SPLIT, fdf);
	while (x < fdf->x_max)
	{
		color_str = ft_strchr(token_arr[x], ',');
		if (color_str)
		{
			fdf->col_prov = 1;
			fdf->color[y][x] = get_color_code(color_str, token_arr, fdf);
		}
		else
			fdf->color[y][x] = WIRE_COLOR;
		x++;
	}
	free_str_arr(&token_arr);
}

/*
Parses the color values of the map into the fdf structure.
If no color code is provided for an entry, the default 'WIRE_COLOR' is used.
The function allocates memory, reads and checks the values color codes,
and stores them in the int matrix 'fdf->color'.
*/
void	get_color(t_fdf *fdf, char *file)
{
	int	x;

	x = 0;
	fdf->color = (int **)ft_calloc(fdf->y_max, sizeof(int *));
	if (!fdf->color)
		perror_and_exit(ERR_MALLOC, fdf);
	fdf->fd = open(file, O_RDONLY);
	if (-1 == fdf->fd)
		perror_and_exit(file, fdf);
	fdf->line = get_next_line(fdf->fd);
	while (fdf->line != NULL)
	{
		fdf->color[x] = (int *)ft_calloc(fdf->x_max, sizeof(int));
		if (!fdf->color[x])
			perror_and_exit(ERR_MALLOC, fdf);
		parse_color(fdf, x);
		free(fdf->line);
		fdf->line = get_next_line(fdf->fd);
		x++;
	}
	close(fdf->fd);
}
