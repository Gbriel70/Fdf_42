/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:21:51 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:30:15 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void draw_vertical_line(t_data_draw_line *line, t_point start, t_point end)
{
    int y = (int)start.y;
    while (y != (int)end.y)
    {
        put_pixel(line->img, (int)start.x, y, start.color);
        y += line->inc_y;
    }
}

void draw_horizontal_line(t_data_draw_line *line, t_point start, t_point end)
{
    int x = (int)start.x;
    while (x != (int)end.x)
    {
        put_pixel(line->img, x, (int)start.y, start.color);
        x += line->inc_x;
    }
}

void draw_line_larger_x_axis(t_data_draw_line *line, t_point start, t_point end)
{
    int x = (int)start.x;
    int y = (int)start.y;
    int d = 2 * line->dy - line->dx;
    int d1 = 2 * line->dy;
    int d2 = 2 * (line->dy - line->dx);

    while (x != (int)end.x)
    {
        put_pixel(line->img, x, y, start.color);
        if (d > 0)
        {
            y += line->inc_y;
            d += d2;
        }
        else
        {
            d += d1;
        }
        x += line->inc_x;
    }
}

void draw_line_larger_y_axis(t_data_draw_line *line, t_point start, t_point end)
{
    int x = (int)start.x;
    int y = (int)start.y;
    int d = 2 * line->dx - line->dy;
    int d1 = 2 * line->dx;
    int d2 = 2 * (line->dx - line->dy);

    while (y != (int)end.y)
    {
        put_pixel(line->img, x, y, start.color);
        if (d > 0)
        {
            x += line->inc_x;
            d += d2;
        }
        else
        {
            d += d1;
        }
        y += line->inc_y;
    }
}

void draw_line(mlx_image_t *img, t_point start, t_point end)
{
    t_data_draw_line *line;

    line = new_line_data(img, start, end);
    if (line->dx == 0)
        draw_vertical_line(line, start, end);
    else if (line->dy == 0)
        draw_horizontal_line(line, start, end);
    else
    {
        if (line->dx >= line->dy)
            draw_line_larger_x_axis(line, start, end);
        else
            draw_line_larger_y_axis(line, start, end);
    }
    free(line);
}
