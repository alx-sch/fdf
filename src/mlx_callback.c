/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_callback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:34:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/18 15:52:21 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	if (fdf->win)
		fdf->close_window = 1;
	return (0);
}

// void move_image(t_fdf *fdf, int dx, int dy) {
//     // Update the coordinates of the displayed portion of the image
// 	fdf->map_x += dx;
// 	fdf->map_y += dy;

//     // Redraw the image with the updated coordinates
//     // You'll need to implement the rendering logic here
//     // For simplicity, let's assume fdf_render_image() is a function that renders the image based on fdf->img_x and fdf->img_y
// 	render_image(fdf);
// }

int	handle_keypress(int keycode, t_fdf *fdf)
{
	// if (keycode == 'A' || keycode == 'a') // Left arrow key
	// 	move_image(fdf, -10, 0); // Move left by 10 pixels
	// else if (keycode == 'D' || keycode == 'd') // Right arrow key
	// 	move_image(fdf, 10, 0); // Move right by 10 pixels
	// else if (keycode == 'S' || keycode == 's') // Down arrow key
	// 	move_image(fdf, 0, 10); // Move down by 10 pixels
	// else if (keycode == 'W' || keycode == 'w') // Up arrow key
	// 	move_image(fdf, 0, -10); // Move up by 10 pixels
	if (keycode == XK_Escape)
		close_window(fdf);
	return (0);
}
