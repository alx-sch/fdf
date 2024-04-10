/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:13 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/10 18:20:07 by aschenk          ###   ########.fr       */
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
# include <X11/keysym.h> // Macros for key symbols, e.g. XK_Escape
# include <X11/X.h> //Macros releated to the event names/masks, e.g. KeyPress

# define MLX_ERROR 1

# define WINDOW_W 600
# define WINDOW_H 300

# define RED	0xFF0000
# define GREEN	0x00FF00
# define WHITE	0xFFFFFF

// Data structure holding image info, incl. dimensions, pixel data, color, and
// endianess.
//	- void *img:	Pointer to image object. Used when manipulating image as a
//					whole, e.g. loading into memory or passing to redering ftcs.
//	- char *addr:	Pointer to the start of image data -> raw pixel information.
//					Used in operations reading/modifying individual pixels.
//	- int bpp:		Number of bits used to represent each pixel, which
//					defines the color depth: 32 bits (4 bytes) -> TRGB
//	- int line_len:	Length of each line in the image in bytes,
//					indicating the number of bytes needed to store a single
//					row of pixels in the image.
//	- int endian:	Endianness refers to the byte order in which data types are
//					stored in memory (either big or little endian; left to right
//					and right to left, respectively). Used to determine how to
//					interpret image data ('img' and 'addr' members).
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

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

// main.c
int		main(void);

// utils.c
void	msg_and_exit(char *msg, int exit_code);

// libft
int		ft_printf(const char *format, ...);

/*
// MiniLibx

//	Initializes the MiniLibx structure and returns a generic/void pointer
//	to this structure. Holds information such as display and graphics system
//	used, even queues, and so on, which are 'under the hood' and not be
//	accessed directly.
void	*mlx_init(void);

//	Returns pointer to a newly created window with specified properties.
void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);

//	Calls specified callback fct repeatedly with passed parameters (optional).

// Sets up a hook for the main event loop of the MiniLibX library by passing a
// callback function and optional parameters.
int		mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);

//	Sets up keyboard event for the specified window by passing the keycode and
//	optional parameters to the provided callback function.
int		mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);

//	Starts the main event loop of the MiniLibX library, which continuously
//	processes user input events and executes any registered callback functions.
//	This function blocks the program's execution until the user closes the main
//	window or explicitly terminates the program.
void	mlx_loop(void *mlx_ptr);

// Destroys the specified window and releases any associated resources.
void	mlx_destroy_window(void *mlx_ptr, void *win_ptr);

//	Destroys the connection to the graphical system and releases any associated
//	resources.
void	mlx_destroy_display(void *mlx_ptr);

*/

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

#endif
