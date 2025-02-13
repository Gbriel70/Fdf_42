/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:21:51 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 11:08:49 by gcosta-m         ###   ########.fr       */
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

int _round(float num)
{
    if (num < 0)
        return (int)(num - 0.5);
    else
        return (int)(num + 0.5);
}

int _floor(float num)
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
    t_point stt;
    t_point end;
    float grad;
    int steep;
} t_draw_params;

typedef struct s_pixel_params
{
    int x;
    int y;
    float intensity;
    int color;
} t_px_p;

static void	put_px_intsit(mlx_image_t *img, t_px_p *params)
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
    t_px_p px_p;

    ypxl = _floor(yend);
    if (params->steep)
    {
        px_p = (t_px_p){ypxl, point.x, (1 - (yend - ypxl)) * xgap, point.c};
        put_px_intsit(params->img, &px_p);
        px_p = (t_px_p){ypxl + 1, point.x, (yend - ypxl) * xgap, point.c};
        put_px_intsit(params->img, &px_p);
    }
    else
    {
        px_p = (t_px_p){point.x, ypxl, (1 - (yend - ypxl)) * xgap, point.c};
        put_px_intsit(params->img, &px_p);
        px_p = (t_px_p){point.x, ypxl + 1, (yend - ypxl) * xgap, point.c};
        put_px_intsit(params->img, &px_p);
    }
}

static void	draw_endpoints(t_draw_params *params)
{
    float	xend;
    float	yend;
    float	xgap;

    xend = _round(params->stt.x);
    yend = params->stt.y + params->grad * (xend - params->stt.x);
    xgap = 1 - (params->stt.x + 0.5 - _floor(params->stt.x + 0.5));
    draw_endpoint(params, (t_point){xend, params->stt.y, params->stt.c}, yend, xgap);
    xend = _round(params->end.x);
    yend = params->end.y + params->grad * (xend - params->end.x);
    xgap = params->end.x + 0.5 - _floor(params->end.x + 0.5);
    draw_endpoint(params, (t_point){xend, params->end.y, params->end.c}, yend, xgap);
}

static void	draw_line_main(t_draw_params *p)
{
    float	i;
    int		x;
    t_px_p px_p;

    i = p->stt.y + p->grad * (_round(p->stt.x) - p->stt.x) + p->grad;
    x = _round(p->stt.x) + 1;
    while (x < _round(p->end.x))
    {
        if (p->steep)
        {
            px_p = (t_px_p){_floor(i), x, 1 - (i - _floor(i)), p->stt.c};
            put_px_intsit(p->img, &px_p);
            px_p = (t_px_p){_floor(i) + 1, x, i - _floor(i), p->stt.c};
            put_px_intsit(p->img, &px_p);
        }
        else
        {
            px_p = (t_px_p){x, _floor(i), 1 - (i - _floor(i)), p->stt.c};
            put_px_intsit(p->img, &px_p);
            px_p = (t_px_p){x, _floor(i) + 1, i - _floor(i), p->stt.c};
            put_px_intsit(p->img, &px_p);
        }
        i += p->grad;
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
    params.stt = start;
    params.end = end;
    params.grad = gradient;
    params.steep = steep;
    draw_endpoints(&params);
    draw_line_main(&params);
}

void	draw_line(mlx_image_t *img, t_point start, t_point end)
{
    draw_line_xiaolin_wu(img, start, end);
}
