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

#include "../includes/fdf_bonus.h"

static t_point **convert_to_matrix(t_map *s_map, int projection)
{
    t_point **matrix;
    t_map *current;
    int i, j;
    float offset_x, offset_y;

    matrix = (t_point **)malloc(sizeof(t_point *) * s_map->height);
    if (!matrix)
        return (NULL);
    i = 0;
    while (i < s_map->height)
    {
        matrix[i] = (t_point *)malloc(sizeof(t_point) * s_map->width);
        if (!matrix[i])
            return (NULL);
        i++;
    }

    current = s_map;
    i = 0;
    while (i < s_map->height)
    {
        j = 0;
        while (j < s_map->width)
        {
            if (projection == 0)
                isometric_projection(current, &matrix[i][j]);
            else
                parallel_projection(current, &matrix[i][j]);
            current = current->next;
            j++;
        }
        i++;
    }

    // Calcular o offset para centralizar o mapa
    offset_x = (SCREEN_WIDTH - (matrix[s_map->height - 1][s_map->width - 1].x - matrix[0][0].x)) / 2;
    offset_y = (SCREEN_HEIGHT - (matrix[s_map->height - 1][s_map->width - 1].y - matrix[0][0].y)) / 2;

    // Aplicar o offset
    i = 0;
    while (i < s_map->height)
    {
        j = 0;
        while (j < s_map->width)
        {
            matrix[i][j].x += offset_x;
            matrix[i][j].y += offset_y;
            j++;
        }
        i++;
    }

    return (matrix);
}

void draw_map(mlx_image_t *img, t_point **matrix, int width, int height)
{
    int i, j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            put_pixel(img, (int)matrix[i][j].x, (int)matrix[i][j].y, matrix[i][j].color);
            if (j < width - 1)
                draw_line(img, matrix[i][j], matrix[i][j + 1]);
            if (i < height - 1)
                draw_line(img, matrix[i][j], matrix[i + 1][j]);
            j++;
        }
        i++;
    }
}

void render(t_fdf *fdf)
{
    t_point **matrix;

    background(fdf->img);
    matrix = convert_to_matrix(fdf->s_map, fdf->projection);
    if (!matrix)
        return;

    draw_map(fdf->img, matrix, fdf->s_map->width, fdf->s_map->height);
    draw_comands(fdf->mlx);

    // Libere a memória da matriz após o uso
    int i = 0;
    while (i < fdf->s_map->height)
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}
