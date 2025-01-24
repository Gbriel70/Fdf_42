/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:23:24 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:29:59 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_matrix_width	*get_matrix_width(float **map_matrix, t_map *s_map)
{
	t_matrix_width	*s_matrix_width;
	int				x;
	int				y;

	x = 0;
	s_matrix_width = malloc(sizeof(float) * 3);
	s_matrix_width->min_matrix_width = 0;
	s_matrix_width->max_matrix_width = 0;
	while (s_map)
	{
		y = 0;
		if (map_matrix[x][y] < s_matrix_width->min_matrix_width)
			s_matrix_width->min_matrix_width = map_matrix[x][y];
		if (map_matrix[x][y] > s_matrix_width->max_matrix_width)
			s_matrix_width->max_matrix_width = map_matrix[x][y];
		x++;
		s_map = s_map->next;
	}
	if (s_matrix_width->min_matrix_width < 0)
		s_matrix_width->matrix_width = s_matrix_width->max_matrix_width
			+ s_matrix_width->min_matrix_width;
	else
		s_matrix_width->matrix_width = s_matrix_width->max_matrix_width
			- s_matrix_width->min_matrix_width;
	return (s_matrix_width);
}

static t_matrix_height	*get_matrix_height(float **map_matrix, t_map *s_map)
{
	t_matrix_height	*s_matrix_height;
	int				x;
	int				y;

	x = 0;
	s_matrix_height = malloc(sizeof(float) * 3);
	s_matrix_height->min_matrix_height = 0;
	s_matrix_height->max_matrix_height = 0;
	while (s_map)
	{
		y = 1;
		if (map_matrix[x][y] < s_matrix_height->min_matrix_height)
			s_matrix_height->min_matrix_height = map_matrix[x][y];
		if (map_matrix[x][y] > s_matrix_height->max_matrix_height)
			s_matrix_height->max_matrix_height = map_matrix[x][y];
		x++;
		s_map = s_map->next;
	}
	if (s_matrix_height->min_matrix_height < 0)
		s_matrix_height->matrix_height = s_matrix_height->max_matrix_height
			+ s_matrix_height->min_matrix_height;
	else
		s_matrix_height->matrix_height = s_matrix_height->max_matrix_height
			- s_matrix_height->min_matrix_height;
	return (s_matrix_height);
}

t_matrix_dimensions	*get_matrix_dimensions(float **map_matrix, t_map *s_map)
{
	t_matrix_dimensions	*s_matrix_dimensions;
	t_matrix_width		*s_matrix_width;
	t_matrix_height		*s_matrix_height;

	s_matrix_width = get_matrix_width(map_matrix, s_map);
	s_matrix_height = get_matrix_height(map_matrix, s_map);
	s_matrix_dimensions = malloc(sizeof(t_matrix_dimensions));
	s_matrix_dimensions->matrix_width = s_matrix_width->matrix_width;
	s_matrix_dimensions->matrix_height = s_matrix_height->matrix_height;
	free(s_matrix_width);
	free(s_matrix_height);
	return (s_matrix_dimensions);
}

void	get_map_scale(t_map *s_map)
{
	float	bigger;
	float	scale;

	if (s_map->height > s_map->width)
		bigger = s_map->height;
	else
		bigger = s_map->width;
	scale = SCREEN_WIDTH / (bigger * 1.7);
	s_map->scale = scale;
	return ;
}

float	**scale_dimension_matrix(t_map *s_map, float **map_matrix,
		t_matrix_dimensions *s_matrix_dimensions)
{
	float	**converted_matrix;
	float	scale;
	int		x;
	int		y;

	x = 0;
	scale = s_map->scale;
	converted_matrix = malloc(sizeof(float *) * (s_map->height * s_map->width
				+ 2));
	while (s_map)
	{
		y = 0;
		converted_matrix[x] = malloc(sizeof(float) * 2);
		converted_matrix[x][y] = (map_matrix[x][y] * scale) + (SCREEN_WIDTH / 2)
			- (s_matrix_dimensions->matrix_width / 2 * scale);
		converted_matrix[x][y + 1] = (map_matrix[x][y + 1] * scale)
			+ (SCREEN_HEIGHT / 2) - (s_matrix_dimensions->matrix_height / 2
				* scale);
		x++;
		s_map = s_map->next;
	}
	converted_matrix[x] = NULL;
	clean_matrix(map_matrix);
	free(s_matrix_dimensions);
	return (converted_matrix);
}
