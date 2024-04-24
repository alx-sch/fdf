/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:34:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/24 13:46:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains hook functions to intercept and respond to user input,
including key input and window interaction events.
*/

#include "fdf.h"

// IN FILE:

int	handle_keypress(int keycode, t_fdf *fdf);
int	handle_x(t_fdf	*fdf);

/*
Event hook checking key input:
- Esc:	The window is closed, all deallocated memory is freed,
		and the program terminates successfully.
*/
int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
	{
		free_fdf(&fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

/*
Event hook checking for window destruction.
If the destruction signal is received (by clicking the 'x' button),
the window is closed, all deallocated memory is freed, and the program
terminates successfully.
*/
int	handle_x(t_fdf	*fdf)
{
	free_fdf(&fdf);
	exit(EXIT_SUCCESS);
	return (0);
}
