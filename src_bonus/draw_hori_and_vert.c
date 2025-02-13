/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hori_and_vert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:45:29 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/13 13:49:24 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	draw_horizontal_lines(t_drawlines_params *params)
{
	int			x;
	t_point		start;
	t_point		end;
	t_map		*current_map;

	x = 0;
	current_map = params->s_map;
	while (current_map)
	{
		start = (t_point){params->cntd_m[x][0], params->cntd_m[x][1],
			current_map->s_references->color};
		if ((x + 1) % params->width != 0)
		{
			end = (t_point){params->cntd_m[x + 1][0], params->cntd_m[x + 1][1],
				current_map->s_references->color};
			draw_line(params->img, start, end);
		}
		x++;
		current_map = current_map->next;
	}
}

void	draw_vertical_lines(t_drawlines_params *params)
{
	int		x;
	t_point	start;
	t_point	end;

	x = 0;
	while (params->s_map)
	{
		start = (t_point){params->cntd_m[x][0], params->cntd_m[x][1],
			params->s_map->s_references->color};
		if (x < (params->height - 1) * params->width)
		{
			end = (t_point){params->cntd_m[x + params->width][0],
				params->cntd_m[x + params->width][1],
				params->s_map->s_references->color};
			draw_line(params->img, start, end);
		}
		x++;
		params->s_map = params->s_map->next;
	}
}
