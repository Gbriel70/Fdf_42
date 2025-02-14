/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:40:39 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/13 10:40:40 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	ft_swap_points(t_point *a, t_point *b)
{
	t_point	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_float(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	_round(float num)
{
	if (num < 0)
		return ((int)(num - 0.5));
	else
		return ((int)(num + 0.5));
}

int	_floor(float num)
{
	int	int_num;

	int_num = (int)num;
	if (num < int_num)
		return (int_num - 1);
	else
		return (int_num);
}

void	put_px_intsit(mlx_image_t *img, t_px_p *params)
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
