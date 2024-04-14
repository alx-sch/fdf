/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:13 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/15 00:48:59 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h" // libft
# include <X11/keysym.h> // Macros for key symbols, e.g. XK_Escape
# include <X11/X.h> //Macros releated to the event names/masks, e.g. KeyPress
# include <mlx.h> // MiniLibX

# include "colors.h" // Color Macros

# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open, close, read, write
# include <stdio.h> // perror
# include <string.h> // strerror
//# include <pthread.h> // thread-related functions

//	++++++++++++
//	++ MACROS ++
//	++++++++++++

# define BG_COLOR	WHITE	// Set the background color
# define WIRE_COLOR	SKY_BLUE // Set the default color for the wireframe

// Error messages passed to the stderr:

# define ERR_ARG			"ERROR: Use './fdf map_file.fdf'!\n"
# define ERR_FILE_TYPE		"ERROR: Invalid file format, use '.fdf'!\n"
# define ERR_MLX			"ERROR: MLX\n"
# define ERR_MALLOC			"ERROR: malloc failed"
# define ERR_GNL			"ERROR: get_next_line failed"
# define ERR_FILE_STRUC		"ERROR: Invalid map structure!\n"
// Inval. structure: empty, non-rectangular, does not end with single empty line

# define WINDOW_W 600
# define WINDOW_H 300

//	++++++++++++++++
//	++ STRUCTURES ++
//	++++++++++++++++

// Data structure holding image info, incl. dimensions, pixel data, color, and
// endianess.
//	- void *img:	Pointer to image object. Used when manipulating image as a
//					whole, e.g. loading into memory or passing to redering ftcs.
//	- char *data:	Pointer to the start of image data -> raw pixel information.
//					Used in operations reading/modifying individual pixels.
//	- int bpp:		Number of bits used to represent each pixel, which
//					defines the color depth: 32 bits (4 bytes) -> TRGB
//	- int size_len:	Length of each line in the image in bytes,
//					indicating the number of bytes needed to store a single
//					row of pixels in the image.
//	- int endian:	Endianness refers to the byte order in which data types are
//					stored in memory (either big or little endian; left to right
//					and right to left, respectively). Used to determine how to
//					interpret image data ('img' and 'data' members).
typedef struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_len;
	int		endian;
}	t_img;

//	- int color_provided:	Flag if .fdf file provides colors (no: 0, yes: 1).
typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		map_x;
	int		map_y;
	int		**map_z;
	int		**map_color;
	int		color_provided;
}	t_fdf;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++



//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++


// map_check.c

int		ft_fgetc(int fd);
void	check_file(char *file, int fd_2);

// map_get.c

int		check_and_get_map_x(char *file);
int		check_and_get_map_y(char *file);

// fdf_init.c

void	init_fdf(t_fdf *fdf, char *file);

// fdf_free.c

void	free_fdf(t_fdf *fdf);

// values_get.c

void	get_map_z(t_fdf *fdf, char *file);
void	get_map_color(t_fdf *fdf, char *file);

// mlx_hooks.c

int		handle_keypress(int keycode, t_fdf *fdf);
int		handle_event(t_fdf *fdf);
int		close_window(t_fdf *fdf);

// mlx_render.c

int		render(t_fdf *fdf);

// utils.c

void	msg_and_exit(char *msg, t_fdf *fdf);
void	perror_and_exit(char *msg, t_fdf *fdf);

#endif
