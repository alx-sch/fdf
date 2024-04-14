/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:53:16 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 00:47:30 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	msg_and_exit(char *msg, t_fdf *fdf);
void	perror_and_exit(char *msg, t_fdf *fdf);

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
