/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:23:38 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:23:40 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static float	**get_map_matrix(t_map *s_map, int projection)
{
    float	**map_matrix;
    int		x;

    x = 0;
    map_matrix = (float **)malloc(sizeof(float *) * (s_map->height * s_map->width + 2));
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
            //oblique_projection(s_map, map_matrix, x);
            //perspective_projection(s_map, map_matrix, x);
            //dimetric_projection(s_map, map_matrix, x);
            //spherical_projection(s_map, map_matrix, x);
            //cylindrical_projection(s_map, map_matrix, x);
            trimetric_projection(s_map, map_matrix, x);
        x++;
        s_map = s_map->next;
    }
    map_matrix[x] = NULL;
    return (map_matrix);
}

static float	**convert_matrix(t_map *s_map, float **map_matrix)
{
    float				**converted_matrix;
    t_matrix_dimensions	*s_matrix_dimensions;

    s_matrix_dimensions = get_matrix_dimensions(map_matrix, s_map);
    get_map_scale(s_map);
    converted_matrix = scale_dimension_matrix(s_map, map_matrix, s_matrix_dimensions);
    return (converted_matrix);
}

static void	draw_map(t_map *s_map, mlx_image_t *img, float **converted_matrix)
{
    int	x;
    int	width;
    int	height;

    x = 0;
    width = s_map->width;
    height = s_map->height;
    while (s_map)
    {
        t_point start = {converted_matrix[x][0], converted_matrix[x][1], s_map->s_references->color};
        if ((x + 1) % width != 0)
        {
            t_point end = {converted_matrix[x + 1][0], converted_matrix[x + 1][1], s_map->s_references->color};
            draw_line(img, start, end);
        }
        if (x < (height - 1) * width)
        {
            t_point end = {converted_matrix[x + width][0], converted_matrix[x + width][1], s_map->s_references->color};
            draw_line(img, start, end);
        }
        x++;
        s_map = s_map->next;
    }
    clean_matrix(converted_matrix);
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
