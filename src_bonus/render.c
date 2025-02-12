/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:23:38 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 17:07:03 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static float	**get_map_matrix(t_map *s_map, int projection)
{
	float	**map_matrix;
	int		x;

	x = 0;
	map_matrix = malloc(sizeof(float *) * (s_map->height * s_map->width + 2));
	if (!map_matrix)
		return (NULL);
	while (s_map)
	{
		map_matrix[x] = malloc(sizeof(float) * 2);
		if (!map_matrix[x])
			clean_matrix(map_matrix);
		if (projection == 0)
			isometric_projection(s_map, map_matrix, x);
		else if (projection == 1)
			parallel_projection(s_map, map_matrix, x);
		else
			trimetric_projection(s_map, map_matrix, x);
		x++;
		s_map = s_map->next;
	}
	map_matrix[x] = NULL;
	return (map_matrix);
}

static float	**convert_matrix(t_map *s_map, float **map_matrix)
{
	float				**converted_m;
	t_matrix_dimensions	*s_m_dimensions;

	s_m_dimensions = get_matrix_dimensions(map_matrix, s_map);
	get_map_scale(s_map);
	converted_m = scale_dimension_matrix(s_map, map_matrix, s_m_dimensions);
	return (converted_m);
}

static void	draw_map(t_map *s_map, mlx_image_t *img, float **cntd_m)
{
	int	x;
	int	width;
	int	height;

	x = 0;
	width = s_map->width;
	height = s_map->height;
	t_point start;
	t_point end;
	while (s_map)
	{
		start = (t_point){cntd_m[x][0], cntd_m[x][1], s_map->s_references->color};
		if ((x + 1) % width != 0)
		{
			end = (t_point){cntd_m[x + 1][0], cntd_m[x + 1][1], s_map->s_references->color};
			draw_line(img, start, end);
		}
		if (x < (height - 1) * width)
		{
			end = (t_point){cntd_m[x + width][0], cntd_m[x + width][1], s_map->s_references->color};
			draw_line(img, start, end);
		}
		x++;
		s_map = s_map->next;
	}
	clean_matrix(cntd_m);
}

void	render(t_fdf *fdf)
{
	float	**map_matrix;
	float	**converted_matrix;

	background(fdf->img);
	map_matrix = get_map_matrix(fdf->s_map, fdf->projection);
	converted_matrix = convert_matrix(fdf->s_map, map_matrix);
	draw_map(fdf->s_map, fdf->img, converted_matrix);
	draw_comands(fdf->mlx);
}
