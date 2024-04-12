/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/12 23:14:01 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// map.c

int		get_map_x(char *file);
int		get_map_y(char *file);
int		is_map_rect(char *file, int map_x);

// utils.c

void	msg_and_exit(char *msg, int exit_code);
void	perror_and_exit(char *msg, int exit_code);

static void	check_map(t_fdf	*fdf, char *file)
{
	if (fdf->map_x == -1)
		msg_and_exit(ERR_FILE_EMPTY, EXIT_FILE_EMPTY);
	if (!is_map_rect(file, fdf->map_x))
		msg_and_exit(ERR_FILE_STRUC, EXIT_FILE_STRUC);
}

void	init_fdf(t_fdf *fdf, char *file)
{

	fdf->map_x = get_map_x(file);
	fdf->map_y = get_map_y(file);
	check_map(fdf, file);
	fdf->map = (int **)ft_calloc(fdf->map_y, sizeof(int *));
	if (!fdf->map)
		perror_and_exit("malloc", EXIT_FAILURE);
}