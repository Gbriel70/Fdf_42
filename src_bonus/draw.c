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

void	ft_swap_points(t_point *a, t_point *b)
{
    t_point temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void	ft_swap2(float *a, float *b)
{
    float temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

static void	put_pixel_with_intensity(mlx_image_t *img, int x, int y,
    float intensity, int color)
{
    float	min_intensity;
    int		r;
    int		g;
    int		b;
    int		new_color;

    min_intensity = 0.9;
    intensity = intensity * (1 - min_intensity) + min_intensity;
    r = ((color >> 16) & 0xFF) * intensity;
    g = ((color >> 8) & 0xFF) * intensity;
    b = (color & 0xFF) * intensity;
    new_color = (r << 16) | (g << 8) | b;
    put_pixel(img, x, y, new_color);
}

static void	draw_endpoint(mlx_image_t *img, t_point point, float yend,
    float xgap, int steep)
{
    int	ypxl;

    ypxl = floor(yend);
    if (steep)
    {
        put_pixel_with_intensity(img, ypxl, point.x,
            (1 - (yend - ypxl)) * xgap, point.color);
        put_pixel_with_intensity(img, ypxl + 1, point.x,
            (yend - ypxl) * xgap, point.color);
    }
    else
    {
        put_pixel_with_intensity(img, point.x, ypxl,
            (1 - (yend - ypxl)) * xgap, point.color);
        put_pixel_with_intensity(img, point.x, ypxl + 1,
            (yend - ypxl) * xgap, point.color);
    }
}

static void	draw_endpoints(mlx_image_t *img, t_point start, t_point end,
    float gradient, int steep)
{
    float	xend;
    float	yend;
    float	xgap;

    xend = round(start.x);
    yend = start.y + gradient * (xend - start.x);
    xgap = 1 - (start.x + 0.5 - floor(start.x + 0.5));
    draw_endpoint(img, (t_point){xend, start.y, start.color}, yend, xgap, steep);
    xend = round(end.x);
    yend = end.y + gradient * (xend - end.x);
    xgap = end.x + 0.5 - floor(end.x + 0.5);
    draw_endpoint(img, (t_point){xend, end.y, end.color}, yend, xgap, steep);
}

static void	draw_line_main(mlx_image_t *img, t_point start, t_point end,
    float gradient, int steep)
{
    float	intery;
    int		x;

    intery = start.y + gradient * (round(start.x) - start.x) + gradient;
    x = round(start.x) + 1;
    while (x < round(end.x))
    {
        if (steep)
        {
            put_pixel_with_intensity(img, floor(intery), x,
                1 - (intery - floor(intery)), start.color);
            put_pixel_with_intensity(img, floor(intery) + 1, x,
                intery - floor(intery), start.color);
        }
        else
        {
            put_pixel_with_intensity(img, x, floor(intery),
                1 - (intery - floor(intery)), start.color);
            put_pixel_with_intensity(img, x, floor(intery) + 1,
                intery - floor(intery), start.color);
        }
        intery += gradient;
        x++;
    }
}

static void	draw_line_xiaolin_wu(mlx_image_t *img, t_point start, t_point end)
{
    int		steep;
    float	dx;
    float	dy;
    float	gradient;

    steep = ft_abs(end.y - start.y) > ft_abs(end.x - start.x);
    if (steep)
    {
        ft_swap2(&start.x, &start.y);
        ft_swap2(&end.x, &end.y);
    }
    if (start.x > end.x)
        ft_swap_points(&start, &end);
    dx = end.x - start.x;
    dy = end.y - start.y;
    gradient = dy / dx;
    draw_endpoints(img, start, end, gradient, steep);
    draw_line_main(img, start, end, gradient, steep);
}

void	draw_line(mlx_image_t *img, t_point start, t_point end)
{
    draw_line_xiaolin_wu(img, start, end);
}
