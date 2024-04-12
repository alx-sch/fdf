/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/12 17:44:28 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// utils.c

void	perror_and_exit(char *msg, int exit_code);
int		count_words(char *line);

// libft

size_t	ft_strlen(const char *s);

int	is_fdf(char *s)
{
	size_t	len;

	if (!*s)
		return (0);
	len = ft_strlen(s);
	while (len >= 0 && s[len] != '.')
		len--;
	if (!ft_strcmp(s + len, ".fdf"))
		return (1);
	return (0);
}

// Width of first map row.
int	get_map_x(char *file)
{
	int		fd;
	int		map_x;
	char	*line;

	fd = open(file, O_RDONLY);
	if (-1 == fd)
		perror_and_exit(file, EXIT_FAILURE);
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

// returns lines in file.
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

// Checks if al lines got the same number of entries
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
			get_next_line(-1);
			return (0);
		}
	}
	return (1);
}

// void	read_file(char *file, t_fdf *fdf)
// {
// 	fdf->map_x = get_width(file);
// 	fdf->map_y = get_height(file);
// 	if (!fdf->map_x || !fdf->map_y)
// 		(ft_putendl_fd(ERR_EMTY, 2), exit(EXIT_FAILURE));
// }
