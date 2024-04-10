/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:13 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/10 14:21:00 by aschenk          ###   ########.fr       */
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

# define WINDOW_W 600
# define WINDOW_H 300

// Data structure holding image info, incl. dimensions, pixel data, color, and
// endianess.
//	- void *img:	Pointer to image object. Used when manipulating image as a
//					whole, e.g. loading into memory or passing to redering ftcs.
//	- char *addr:	Pointer to the start of image data -> raw pixel information.
//					Used in operations reading/modifying individual pixels.
//	- int bits_per_pixel:	Number of bits used to represent each pixel, which
//							defines the color depth: 32 bits (4 bytes) -> TRGB
//	- int size_line:	Size/length of each line in the image in bytes,
//						indicating the number of bytes needed to store a single
//						row of pixels in the image.
//	- int endian:	Endianness refers to the byte order in which data types are
//					stored in memory (either big or little endian; left to right
//					and right to left, respectively). Used to determine how to
//					interpret image data ('img' and 'addr' members).
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_data;

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
