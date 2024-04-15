/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 16:08:09 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "fdf.h"

// FILE

void	check_file(char *file, int fd_2);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Used in check_file().
Verifies if the given 'file' ends with the '.fdf' extension.
If it doesn't, the function closes the file descriptor 'fd' and exits
the program, indicating an invalid file type.
If it does end with '.fdf', no action is taken.
*/
static void	check_if_fdf(char *file, int fd)
{
	size_t	len;

	len = ft_strlen(file);
	while (len >= 0 && file[len] != '.')
		len--;
	if (ft_strcmp(file + len, ".fdf"))
	{
		close(fd);
		msg_and_exit(ERR_FILE_TYPE, NULL);
	}
}

/*
Used in check_and_get_map_y().
Verifies the structure and validity of a given file.
It closes the passed 'fd_2' and terminates the program if:
- The file does not end with the '.fdf' extension.
- The file does not end with a single empty line.
*/
void	check_file(char *file, int fd_2)
{
	int	fd;
	int	c;
	int	c_prev;

	check_if_fdf(file, fd_2);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_and_exit(file, NULL);
	c = -1;
	while (c != '\0')
	{
		c_prev = c;
		c = ft_fgetc(fd);
		if (c == '\0')
		{
			if (c_prev != '\n')
			{
				close(fd);
				close(fd_2);
				msg_and_exit(ERR_FILE_STRUC, NULL);
			}
		}
	}
	close (fd);
}
