/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:55:47 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/10 13:56:21 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Draws a single pixel of a specified color at the specified coordinates on
// an image or window represented by the data structure.
// It calculates the memory address where the pixel will be drawn and directly
// assigns the color value to that memory location.
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}