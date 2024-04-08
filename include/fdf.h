/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:13 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/08 15:28:30 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h> // malloc, free, exit, access, dup2, execv
# include <fcntl.h> // open
# include <unistd.h> // fork, pipe, macros like 'STDERR_FILENO'
# include <stdio.h> // perror
# include <string.h> // strerror
# include <errno.h> // errno
# include <sys/wait.h> // waitpid

//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

// main.c
int		main(int argc, char **argv);

// libft
int		ft_printf(const char *format, ...);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

#endif
