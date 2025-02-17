/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:23:38 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/17 10:12:27 by gcosta-m         ###   ########.fr       */
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
	t_drawlines_params	params;

	params.img = img;
	params.s_map = s_map;
	params.cntd_m = cntd_m;
	params.width = s_map->width;
	params.height = s_map->height;
	draw_horizontal_lines(&params);
	draw_vertical_lines(&params);
	clean_matrix(cntd_m);
}

void	render(t_fdf *fdf)
{
	float	**map_matrix;
	float	**converted_matrix;

	map_matrix = get_map_matrix(fdf->s_map, fdf->projection);
	if (!map_matrix)
		return ((void)print_return("Error: Memory allocation failed\n", 1));
	converted_matrix = convert_matrix(fdf->s_map, map_matrix);
	if (!converted_matrix)
	{
		clean_matrix(map_matrix);
		return ((void)print_return("Error: Memory allocation failed\n", 1));
	}
	background(fdf->img);
	draw_map(fdf->s_map, fdf->img, converted_matrix);
	draw_comands(fdf->mlx);
}
