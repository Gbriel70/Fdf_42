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

void	ft_swap_float(float *a, float *b)
{
    float temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int ft_round(float num)
{
    if (num < 0)
        return (int)(num - 0.5);
    else
        return (int)(num + 0.5);
}

int ft_floor(float num)
{
    int int_num;

    int_num = (int)num;
    if (num < int_num)
        return int_num - 1;
    else
        return int_num;
}

typedef struct s_draw_params
{
    mlx_image_t *img;
    t_point start;
    t_point end;
    float gradient;
    int steep;
} t_draw_params;

typedef struct s_pixel_params
{
    int x;
    int y;
    float intensity;
    int color;
} t_pixel_params;

static void	put_pixel_with_intensity(mlx_image_t *img, t_pixel_params *params)
{
    float	min_intensity;
    int		r;
    int		g;
    int		b;
    int		new_color;

    min_intensity = 0.8;
    params->intensity = params->intensity * (1 - min_intensity) + min_intensity;
    r = ((params->color >> 16) & 0xFF) * params->intensity;
    g = ((params->color >> 8) & 0xFF) * params->intensity;
    b = (params->color & 0xFF) * params->intensity;
    new_color = (r << 16) | (g << 8) | b;
    put_pixel(img, params->x, params->y, new_color);
}

static void	draw_endpoint(t_draw_params *params, t_point point, float yend,
    float xgap)
{
    int	ypxl;
    t_pixel_params pixel_params;

    ypxl = ft_floor(yend);
    if (params->steep)
    {
        pixel_params = (t_pixel_params){ypxl, point.x, (1 - (yend - ypxl)) * xgap, point.color};
        put_pixel_with_intensity(params->img, &pixel_params);
        pixel_params = (t_pixel_params){ypxl + 1, point.x, (yend - ypxl) * xgap, point.color};
        put_pixel_with_intensity(params->img, &pixel_params);
    }
    else
    {
        pixel_params = (t_pixel_params){point.x, ypxl, (1 - (yend - ypxl)) * xgap, point.color};
        put_pixel_with_intensity(params->img, &pixel_params);
        pixel_params = (t_pixel_params){point.x, ypxl + 1, (yend - ypxl) * xgap, point.color};
        put_pixel_with_intensity(params->img, &pixel_params);
    }
}

static void	draw_endpoints(t_draw_params *params)
{
    float	xend;
    float	yend;
    float	xgap;

    xend = ft_round(params->start.x);
    yend = params->start.y + params->gradient * (xend - params->start.x);
    xgap = 1 - (params->start.x + 0.5 - ft_floor(params->start.x + 0.5));
    draw_endpoint(params, (t_point){xend, params->start.y, params->start.color}, yend, xgap);
    xend = ft_round(params->end.x);
    yend = params->end.y + params->gradient * (xend - params->end.x);
    xgap = params->end.x + 0.5 - ft_floor(params->end.x + 0.5);
    draw_endpoint(params, (t_point){xend, params->end.y, params->end.color}, yend, xgap);
}

static void	draw_line_main(t_draw_params *params)
{
    float	intery;
    int		x;

    intery = params->start.y + params->gradient * (ft_round(params->start.x) - params->start.x) + params->gradient;
    x = ft_round(params->start.x) + 1;
    while (x < ft_round(params->end.x))
    {
        if (params->steep)
        {
            t_pixel_params pixel_params = {ft_floor(intery), x, 1 - (intery - ft_floor(intery)), params->start.color};
            put_pixel_with_intensity(params->img, &pixel_params);
            pixel_params = (t_pixel_params){ft_floor(intery) + 1, x, intery - ft_floor(intery), params->start.color};
            put_pixel_with_intensity(params->img, &pixel_params);
        }
        else
        {
            t_pixel_params pixel_params = {x, ft_floor(intery), 1 - (intery - ft_floor(intery)), params->start.color};
            put_pixel_with_intensity(params->img, &pixel_params);
            pixel_params = (t_pixel_params){x, ft_floor(intery) + 1, intery - ft_floor(intery), params->start.color};
            put_pixel_with_intensity(params->img, &pixel_params);
        }
        intery += params->gradient;
        x++;
    }
}

static void	draw_line_xiaolin_wu(mlx_image_t *img, t_point start, t_point end)
{
    int		steep;
    float	dx;
    float	dy;
    float	gradient;
    t_draw_params params;

    steep = ft_abs(end.y - start.y) > ft_abs(end.x - start.x);
    if (steep)
    {
        ft_swap_float(&start.x, &start.y);
        ft_swap_float(&end.x, &end.y);
    }
    if (start.x > end.x)
        ft_swap_points(&start, &end);
    dx = end.x - start.x;
    dy = end.y - start.y;
    gradient = dy / dx;
    params.img = img;
    params.start = start;
    params.end = end;
    params.gradient = gradient;
    params.steep = steep;
    draw_endpoints(&params);
    draw_line_main(&params);
}

void	draw_line(mlx_image_t *img, t_point start, t_point end)
{
    draw_line_xiaolin_wu(img, start, end);
}
