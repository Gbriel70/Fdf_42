/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-camera_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:25:15 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/17 10:11:57 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	move_up(t_map *map, float distance, int projection)
{
	t_map	*current;

	current = map;
	while (current)
	{
		if (projection == 0)
		{
			current->s_references->y -= distance * cos(COS_30);
			current->s_references->x -= distance * sin(SIN_30);
		}
		else
		{
			current->s_references->y -= distance;
		}
		current = current->next;
	}
}

void	move_down(t_map *map, float distance, int projection)
{
	t_map	*current;

	current = map;
	while (current)
	{
		if (projection == 0)
		{
			current->s_references->y += distance * cos(COS_30);
			current->s_references->x += distance * sin(SIN_30);
		}
		else
		{
			current->s_references->y += distance;
		}
		current = current->next;
	}
}

void	move_left(t_map *map, float distance, int projection)
{
	t_map	*current;

	current = map;
	while (current)
	{
		if (projection == 0)
		{
			current->s_references->x -= distance * cos(COS_30);
			current->s_references->y += distance * sin(SIN_30);
		}
		else
		{
			current->s_references->x -= distance;
		}
		current = current->next;
	}
}

void	move_right(t_map *map, float distance, int projection)
{
	t_map	*current;

	current = map;
	while (current)
	{
		if (projection == 0)
		{
			current->s_references->x += distance * cos(COS_30);
			current->s_references->y -= distance * sin(SIN_30);
		}
		else
		{
			current->s_references->x += distance;
		}
		current = current->next;
	}
}
