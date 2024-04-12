/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/12 23:17:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

int		get_map_x(char *file);
int		get_map_y(char *file);
int		is_map_rect(char *file, int map_x);

// utils.c

void	perror_and_exit(char *msg, int exit_code);
int		count_words(const char *str);

// libft

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Checks if a given string ends with ".fdf". If it does, it returns 1;
otherwise, it returns 0.
*/
static int	is_fdf(char *str)
{
	size_t	len;

	if (!*str)
		return (0);
	len = ft_strlen(str);
	while (len >= 0 && str[len] != '.')
		len--;
	if (!ft_strcmp(str + len, ".fdf"))
		return (1);
	return (0);
}

/*
Opens the 'file' and reads the first line using get_next_line().
Exits the program if passed file is not of type '.fdf'.
It then counts the number of words in that line and returns the count as
the width of the map.
If the file cannot be opened or there are no lines to read, it returns -1.
*/
int	get_map_x(char *file)
{
	int		fd;
	int		map_x;
	char	*line;

	fd = open(file, O_RDONLY);
	if (-1 == fd)
		perror_and_exit(file, EXIT_FAILURE);
	if (!is_fdf(file))
	{
		close(fd);
		msg_and_exit(ERR_FILE_TYPE, EXIT_FILE_TYPE);
	}
	map_x = -1;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (map_x);
	}
	map_x = count_words(line);
	free(line);
	close(fd);
	return (map_x);
}

/*
Opens the 'file' and reads each line using get_next_line().
It counts the number of lines read until there are no more lines left.
Finally, it returns the total count of lines read (height of the map).
If the file cannot be opened, it returns 0.
*/
int	get_map_y(char *file)
{
	int		fd;
	int		map_y;
	char	*line;

	fd = open(file, O_RDONLY);
	if (-1 == fd)
		perror_and_exit(file, EXIT_FAILURE);
	map_y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (map_y);
		}
		free(line);
		map_y++;
	}
}

/*
Opens the 'file' and reads each line using get_next_line().
It counts the number of words in each line and compares it to 'map_x'
(width of map in first line).
If any line has a different number of words than 'map_x', indicating
that the map is not rectangular, the function returns 0.
Otherwise, it continues reading lines until the EOF, and then returns 1,
indicating that the map is rectangular.
*/
int	is_map_rect(char *file, int map_x)
{
	int		fd;
	int		line_x;
	char	*line;

	fd = open(file, O_RDONLY);
	if (-1 == fd)
		perror_and_exit(file, EXIT_FAILURE);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			break ;
		}
		line_x = count_words(line);
		free(line);
		if (line_x != map_x)
		{
			close(fd);
			get_next_line(-1);
			return (0);
		}
	}
	return (1);
}
