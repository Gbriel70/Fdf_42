/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:21:51 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/13 10:40:25 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

typedef struct s_draw_params
{
	mlx_image_t	*img;
	t_point		stt;
	t_point		end;
	float		grad;
	int			steep;
}				t_draw_params;

static void	draw_endpoint(t_draw_params *params, t_point point, float yend,
		float xgap)
{
	int		ypxl;
	t_px_p	px_p;

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
	draw_endpoint(params, (t_point){xend, params->stt.y, params->stt.c}, yend,
		xgap);
	xend = _round(params->end.x);
	yend = params->end.y + params->grad * (xend - params->end.x);
	xgap = params->end.x + 0.5 - _floor(params->end.x + 0.5);
	draw_endpoint(params, (t_point){xend, params->end.y, params->end.c}, yend,
		xgap);
}

static void	draw_line_main(t_draw_params *p)
{
	float	i;
	int		x;
	t_px_p	px_p;

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
	int				steep;
	float			dx;
	float			dy;
	float			gradient;
	t_draw_params	params;

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
