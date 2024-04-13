/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/13 18:20:59 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// map.c

int		check_and_count_lines(char *file);
int		check_and_count_values_per_line(char *file);

// utils.c

void	perror_and_exit(char *msg, int exit_code);

// libft

void	*ft_calloc(size_t nmemb, size_t size);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

void	init_fdf(t_fdf *fdf, char *file)
{
	fdf->map_y = check_and_count_lines(file);
	fdf->map_x = check_and_count_values_per_line(file);
	fdf->map = (int **)ft_calloc(fdf->map_y, sizeof(int *));
	if (!fdf->map)
		perror_and_exit("malloc", EXIT_FAILURE);
}
