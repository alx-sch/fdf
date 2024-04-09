/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:13 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/09 17:03:29 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open, close, read, write
# include <stdio.h> // perror
# include <string.h> // strerror
# include <mlx.h> // MiniLibX
# include "../src/libft/libft.h" // libft


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

// main.c
int		main(void);

// libft
int		ft_printf(const char *format, ...);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

#endif
