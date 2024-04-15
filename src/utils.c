/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:53:16 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 19:17:29 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	msg_and_exit(char *msg, t_fdf *fdf);
void	perror_and_exit(char *msg, t_fdf *fdf);
int		ft_fgetc(int fd);
void	free_arr(char **array);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Prints an error message to stderr, frees memory allocated within the
fdf structure and exits the program.
*/
void	msg_and_exit(char *msg, t_fdf *fdf)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (fdf)
		free_fdf(fdf);
	exit(EXIT_FAILURE);
}

/*
Prints an error message to stderr via perror(), which also prints the last
encountered error and frees memory allocated within the fdf structure.
Then, exits the program.
*/
void	perror_and_exit(char *msg, t_fdf *fdf)
{
	perror(msg);
	if (fdf)
		free_fdf(fdf);
	exit(EXIT_FAILURE);
}

/*
Used in check_and_get_map_y() and check_file().
Reads one character at a time from the file descriptor 'fd'.
Advances the file pointer with each call.
*/
int	ft_fgetc(int fd)
{
	char	c;
	ssize_t	bytes_read;

	bytes_read = read(fd, &c, 1);
	if (bytes_read == 1)
		return ((int)c);
	else
		return (0);
}

/*
Used in parse_map_z() and parse_map_color().
Frees the memory allocated for an array of strings.
*/
void	free_arr(char **array)
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