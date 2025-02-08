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

static void put_pixel_with_intensity(mlx_image_t *img, int x, int y, float intensity, int color)
{
    float min_intensity = 0.6; // Valor mínimo de intensidade para evitar cores muito escuras
    intensity = intensity * (1 - min_intensity) + min_intensity;

    int r = ((color >> 16) & 0xFF) * intensity;
    int g = ((color >> 8) & 0xFF) * intensity;
    int b = (color & 0xFF) * intensity;
    int new_color = (r << 16) | (g << 8) | b;
    put_pixel(img, x, y, new_color);
}

static void draw_vertical_line_xiaolin_wu(mlx_image_t *img, t_point start, t_point end)
{
    if (start.y > end.y)
    {
        t_point temp = start;
        start = end;
        end = temp;
    }

    float gradient = (end.x - start.x) / (end.y - start.y);
    float xend = round(start.y);
    float yend = start.x + gradient * (xend - start.y);
    float xgap = 1 - (start.y + 0.5 - floor(start.y + 0.5));
    int xpxl1 = xend;
    int ypxl1 = floor(yend);
    put_pixel_with_intensity(img, ypxl1, xpxl1, (1 - (yend - ypxl1)) * xgap, start.color);
    put_pixel_with_intensity(img, ypxl1 + 1, xpxl1, (yend - ypxl1) * xgap, start.color);
    float intery = yend + gradient;

    xend = round(end.y);
    yend = end.x + gradient * (xend - end.y);
    xgap = end.y + 0.5 - floor(end.y + 0.5);
    int xpxl2 = xend;
    int ypxl2 = floor(yend);
    put_pixel_with_intensity(img, ypxl2, xpxl2, (1 - (yend - ypxl2)) * xgap, end.color);
    put_pixel_with_intensity(img, ypxl2 + 1, xpxl2, (yend - ypxl2) * xgap, end.color);

    for (int x = xpxl1 + 1; x < xpxl2; x++)
    {
        put_pixel_with_intensity(img, floor(intery), x, 1 - (intery - floor(intery)), start.color);
        put_pixel_with_intensity(img, floor(intery) + 1, x, intery - floor(intery), start.color);
        intery += gradient;
    }
}

static void draw_horizontal_line_xiaolin_wu(mlx_image_t *img, t_point start, t_point end)
{
    if (start.x > end.x)
    {
        t_point temp = start;
        start = end;
        end = temp;
    }

    float gradient = (end.y - start.y) / (end.x - start.x);
    float xend = round(start.x);
    float yend = start.y + gradient * (xend - start.x);
    float xgap = 1 - (start.x + 0.5 - floor(start.x + 0.5));
    int xpxl1 = xend;
    int ypxl1 = floor(yend);
    put_pixel_with_intensity(img, xpxl1, ypxl1, (1 - (yend - ypxl1)) * xgap, start.color);
    put_pixel_with_intensity(img, xpxl1, ypxl1 + 1, (yend - ypxl1) * xgap, start.color);
    float intery = yend + gradient;

    xend = round(end.x);
    yend = end.y + gradient * (xend - end.x);
    xgap = end.x + 0.5 - floor(end.x + 0.5);
    int xpxl2 = xend;
    int ypxl2 = floor(yend);
    put_pixel_with_intensity(img, xpxl2, ypxl2, (1 - (yend - ypxl2)) * xgap, end.color);
    put_pixel_with_intensity(img, xpxl2, ypxl2 + 1, (yend - ypxl2) * xgap, end.color);

    for (int x = xpxl1 + 1; x < xpxl2; x++)
    {
        put_pixel_with_intensity(img, x, floor(intery), 1 - (intery - floor(intery)), start.color);
        put_pixel_with_intensity(img, x, floor(intery) + 1, intery - floor(intery), start.color);
        intery += gradient;
    }
}

static void draw_diagonal_line_xiaolin_wu(mlx_image_t *img, t_point start, t_point end)
{
    if (ft_abs(end.y - start.y) > ft_abs(end.x - start.x))
    {
        if (start.y > end.y)
        {
            t_point temp = start;
            start = end;
            end = temp;
        }

        float gradient = (end.x - start.x) / (end.y - start.y);
        float xend = round(start.y);
        float yend = start.x + gradient * (xend - start.y);
        float xgap = 1 - (start.y + 0.5 - floor(start.y + 0.5));
        int xpxl1 = xend;
        int ypxl1 = floor(yend);
        put_pixel_with_intensity(img, ypxl1, xpxl1, (1 - (yend - ypxl1)) * xgap, start.color);
        put_pixel_with_intensity(img, ypxl1 + 1, xpxl1, (yend - ypxl1) * xgap, start.color);
        float intery = yend + gradient;

        xend = round(end.y);
        yend = end.x + gradient * (xend - end.y);
        xgap = end.y + 0.5 - floor(end.y + 0.5);
        int xpxl2 = xend;
        int ypxl2 = floor(yend);
        put_pixel_with_intensity(img, ypxl2, xpxl2, (1 - (yend - ypxl2)) * xgap, end.color);
        put_pixel_with_intensity(img, ypxl2 + 1, xpxl2, (yend - ypxl2) * xgap, end.color);

        for (int x = xpxl1 + 1; x < xpxl2; x++)
        {
            put_pixel_with_intensity(img, floor(intery), x, 1 - (intery - floor(intery)), start.color);
            put_pixel_with_intensity(img, floor(intery) + 1, x, intery - floor(intery), start.color);
            intery += gradient;
        }
    }
    else
    {
        if (start.x > end.x)
        {
            t_point temp = start;
            start = end;
            end = temp;
        }

        float gradient = (end.y - start.y) / (end.x - start.x);
        float xend = round(start.x);
        float yend = start.y + gradient * (xend - start.x);
        float xgap = 1 - (start.x + 0.5 - floor(start.x + 0.5));
        int xpxl1 = xend;
        int ypxl1 = floor(yend);
        put_pixel_with_intensity(img, xpxl1, ypxl1, (1 - (yend - ypxl1)) * xgap, start.color);
        put_pixel_with_intensity(img, xpxl1, ypxl1 + 1, (yend - ypxl1) * xgap, start.color);
        float intery = yend + gradient;

        xend = round(end.x);
        yend = end.y + gradient * (xend - end.x);
        xgap = end.x + 0.5 - floor(end.x + 0.5);
        int xpxl2 = xend;
        int ypxl2 = floor(yend);
        put_pixel_with_intensity(img, xpxl2, ypxl2, (1 - (yend - ypxl2)) * xgap, end.color);
        put_pixel_with_intensity(img, xpxl2, ypxl2 + 1, (yend - ypxl2) * xgap, end.color);

        for (int x = xpxl1 + 1; x < xpxl2; x++)
        {
            put_pixel_with_intensity(img, x, floor(intery), 1 - (intery - floor(intery)), start.color);
            put_pixel_with_intensity(img, x, floor(intery) + 1, intery - floor(intery), start.color);
            intery += gradient;
        }
    }
}

void draw_line(mlx_image_t *img, t_point start, t_point end)
{
    if (start.x == end.x)
        draw_vertical_line_xiaolin_wu(img, start, end);
    else if (start.y == end.y)
        draw_horizontal_line_xiaolin_wu(img, start, end);
    else
        draw_diagonal_line_xiaolin_wu(img, start, end);
}
