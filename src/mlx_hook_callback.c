/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:34:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/21 21:58:47 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// mlx_key_hook() expects fct with return type int
int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
	{
		free_fdf(&fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	handle_x(t_fdf	*fdf)
{
	free_fdf(&fdf);
	exit(EXIT_SUCCESS);
	return (0);
}
