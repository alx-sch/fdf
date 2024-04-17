/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:34:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/17 18:24:22 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	if (fdf->win)
		fdf->close_window = 1;
	return (0);
}

int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		close_window(fdf);
	return (0);
}
