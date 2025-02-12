/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:23:44 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 11:23:49 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	parallel_projection(t_map *s_map, float **map_matrix, int x)
{
	map_matrix[x][0] = s_map->s_references->x;
	map_matrix[x][1] = s_map->s_references->y;
}

void	isometric_projection(t_map *s_map, float **map_matrix, int x)
{
	map_matrix[x][0] = (s_map->s_references->x - s_map->s_references->y)
		* cos(COS_30);
	map_matrix[x][1] = (s_map->s_references->x + s_map->s_references->y)
		* sin(SIN_30) - 0.15 * s_map->s_references->z;
}

void	trimetric_projection(t_map *s_map, float **map_matrix, int x)
{
	float	angle_x;
	float	angle_y;
	float	angle_z;

	angle_x = M_PI / 6;
	angle_y = M_PI / 6;
	angle_z = M_PI / 6;
	map_matrix[x][0] = s_map->s_references->x * cos(angle_x)
		- s_map->s_references->y * cos(angle_y);
	map_matrix[x][1] = s_map->s_references->x * sin(angle_x)
		+ s_map->s_references->y * sin(angle_y) - s_map->s_references->z
		* cos(angle_z);
}
