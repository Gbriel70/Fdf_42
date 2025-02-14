/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:06:49 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 12:06:53 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	zoom_in(t_map *map, float scale)
{
	t_map	*current;

	current = map;
	while (current)
	{
		current->s_references->x *= scale;
		current->s_references->y *= scale;
		current->s_references->z *= scale;
		current = current->next;
	}
}

void	zoom_out(t_map *map, float scale)
{
	t_map	*current;

	current = map;
	while (current)
	{
		current->s_references->x /= scale;
		current->s_references->y /= scale;
		current->s_references->z /= scale;
		current = current->next;
	}
}
