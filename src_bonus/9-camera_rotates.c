/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:57 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 12:08:00 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	rotate_x(t_map *map, float angle)
{
	t_map	*current;
	float	tmp_y;
	float	tmp_z;

	current = map;
	while (current)
	{
		tmp_y = current->s_references->y;
		tmp_z = current->s_references->z;
		current->s_references->y = tmp_y * cos(angle) - tmp_z * sin(angle);
		current->s_references->z = tmp_y * sin(angle) + tmp_z * cos(angle);
		current = current->next;
	}
}

void	rotate_y(t_map *map, float angle)
{
	t_map	*current;
	float	tmp_x;
	float	tmp_z;

	current = map;
	while (current)
	{
		tmp_x = current->s_references->x;
		tmp_z = current->s_references->z;
		current->s_references->x = tmp_x * cos(angle) + tmp_z * sin(angle);
		current->s_references->z = -tmp_x * sin(angle) + tmp_z * cos(angle);
		current = current->next;
	}
}

void	rotate_z(t_map *map, float angle)
{
	t_map	*current;
	float	tmp_x;
	float	tmp_y;

	current = map;
	while (current)
	{
		tmp_x = current->s_references->x;
		tmp_y = current->s_references->y;
		current->s_references->x = tmp_x * cos(angle) - tmp_y * sin(angle);
		current->s_references->y = tmp_x * sin(angle) + tmp_y * cos(angle);
		current = current->next;
	}
}
