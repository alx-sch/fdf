/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:34:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/14 15:29:29 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	fdf->win = NULL;
	return (0);
}

int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		close_window(fdf);
	return (0);
}



/* This function needs to exist, but it is useless for the moment */
int	handle_no_event(void *fdf)
{
	fdf = 0;
	return (0);
}
