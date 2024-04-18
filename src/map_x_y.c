/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_x_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/18 16:51:50 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to retrieve the x and y dimensions of the passed
map (width and height) and assigns these values to 'fdf->map_x' and 'fdf->map_y'.
Also checks if the passed map is valid (not empty, not non-rectangular).
*/

#include "fdf.h"

void	get_map_x_and_y(t_fdf *fdf, char *file);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Used in get_map_x_and_y().
Counts count the number of words in the given string, where words are chars
separated by spaces, newline characters, or beginning/end of file.
*/
static int	count_words(const char *str)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			word_count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		else
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	return (word_count);
}

/*
Assigns the x- and y-dimension (map width and height)
to 'fdf->map_x' and 'fdf->map_y', respectively.
Also checks the validity of the map:
- Is map empty (no lines or no entries)?
- Is map not rectangular (not the same amount of entries in each line)?
If not valid,
*/
void	get_map_x_and_y(t_fdf *fdf, char *file)
{
	int		val_count_prev;

	fdf->fd = open(file, O_RDONLY);
	if (-1 == fdf->fd)
		perror_and_exit(file, NULL);
	val_count_prev = -1;
	fdf->line = get_next_line(fdf->fd);
	while (fdf->line != NULL)
	{
		fdf->map_x = count_words(fdf->line);
		if (val_count_prev != -1 && fdf->map_x != val_count_prev)
			msg_and_exit(ERR_FILE_STRUC, fdf);
		val_count_prev = fdf->map_x;
		fdf->map_y += 1;
		free(fdf->line);
		fdf->line = get_next_line(fdf->fd);
	}
	close(fdf->fd);
	if (fdf->map_x == 0 || fdf->map_y == 0)
		msg_and_exit(ERR_FILE_STRUC, NULL);
}
