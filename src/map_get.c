/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 00:46:08 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "fdf.h"

// FILE

int		check_and_get_map_y(char *file);
int		check_and_get_map_x(char *file);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Returns the map height (map_y).
Also checks the validity of the file:
- Exits the program if the passed file is not of type '.fdf'
  or does not end with single empty line).
- If the file is valid, returns the number of lines in the provided file.
*/
int	check_and_get_map_y(char *file)
{
	int	fd;
	int	line_count;
	int	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_and_exit(file, NULL);
	check_file(file, fd);
	line_count = 0;
	c = -1;
	while (c != 0)
	{
		c = ft_fgetc(fd);
		if (c == '\n')
			line_count++;
	}
	close(fd);
	return (line_count);
}

/*
Used in check_and_get_map_x().
Counts count the number of words in the given string, where words are separated
by spaces, newline characters or EOF.
*/
static int	count_words(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		else
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	return (count);
}

/*
Used in check_and_get_map_x().
Exits the program if the passed value counts are not the same, indicating a
non-rectangular map. Before terminating, allocated memory for the passed line
is freed, the passed fd is closed, and the static variable 'stash' used in
get_next_line is freed by calling get_next_line(-1) (necessary when
get_next_line is not executed until it returns NULL).
*/
static void	check_value_counts(int val_count, int val_count_prev, int fd,
	char *line)
{
	if (val_count_prev != -1 && val_count != val_count_prev)
	{
		free(line);
		close(fd);
		get_next_line(-1);
		msg_and_exit(ERR_FILE_STRUC, NULL);
	}
}

/*
Returns the map width (map_x).
Also checks the validity of the file:
- Exits the program if the passed file is empty (no values)
  or is not rectangular (not the same number of entries in each line).
- If the file is valid, returns the number of entries/line.
*/
int	check_and_get_map_x(char *file)
{
	int		fd;
	int		val_count;
	int		val_count_prev;
	char	*line;

	fd = open(file, O_RDONLY);
	if (-1 == fd)
		perror_and_exit(file, NULL);
	val_count_prev = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			if (val_count_prev == 0)
				msg_and_exit(ERR_FILE_STRUC, NULL);
			return (val_count);
		}
		val_count = count_words(line);
		check_value_counts(val_count, val_count_prev, fd, line);
		val_count_prev = val_count;
		free(line);
	}
}
