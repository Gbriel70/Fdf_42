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

static void	draw_vertical_line(t_data_draw_line *line_data,
		float **converted_matrix, int start, int end, int color)
{
	int	x;

	x = 0;
	if ((int)converted_matrix[end][1] > converted_matrix[start][1])
	{
		while ((int)converted_matrix[start][1] != (int)converted_matrix[end][1])
		{
			put_pixel(line_data->img, (int)converted_matrix[start][0],
				(int)converted_matrix[start][1], color);
			converted_matrix[start][1]++;
			x++;
		}
	}
	else
	{
		while ((int)converted_matrix[start][1] != (int)converted_matrix[end][1])
		{
			put_pixel(line_data->img, (int)converted_matrix[start][0],
				(int)converted_matrix[start][1], color);
			converted_matrix[start][1]--;
			x--;
		}
	}
	converted_matrix[start][1] -= x;
}

static void	draw_horizontal_line(t_data_draw_line *line_data,
		float **converted_matrix, int start, int end, int color)
{
	int	x;

	x = 0;
	if ((int)converted_matrix[end][0] > (int)converted_matrix[start][0])
	{
		while ((int)converted_matrix[start][0] != (int)converted_matrix[end][0])
		{
			put_pixel(line_data->img, (int)converted_matrix[start][0],
				(int)converted_matrix[start][1], color);
			converted_matrix[start][0]++;
			x++;
		}
	}
	else
	{
		while ((int)converted_matrix[start][0] != (int)converted_matrix[end][0])
		{
			put_pixel(line_data->img, (int)converted_matrix[start][0],
				(int)converted_matrix[start][1], color);
			converted_matrix[start][0]--;
			x--;
		}
	}
	converted_matrix[start][0] -= x;
}

static void	draw_line_larger_x_axis(t_data_draw_line *line_data,
		float **converted_matrix, int start, int end, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	line_data->control = line_data->dx / 2;
	put_pixel(line_data->img, (int)converted_matrix[start][0],
		(int)converted_matrix[start][1], color);
	while ((int)converted_matrix[start][0] != (int)converted_matrix[end][0])
	{
		converted_matrix[start][0] += line_data->inc_x;
		x += line_data->inc_x;
		line_data->control -= line_data->dy;
		if (line_data->control < 0)
		{
			converted_matrix[start][1] += line_data->inc_y;
			y += line_data->inc_y;
			line_data->control += line_data->dx;
		}
		put_pixel(line_data->img, (int)converted_matrix[start][0],
			(int)converted_matrix[start][1], color);
	}
	converted_matrix[start][0] -= x;
	converted_matrix[start][1] -= y;
}

static void	draw_line_larger_y_axis(t_data_draw_line *line_data,
		float **converted_matrix, int start, int end, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	line_data->control = line_data->dy / 2;
	put_pixel(line_data->img, (int)converted_matrix[start][0],
		(int)converted_matrix[start][1], color);
	while ((int)converted_matrix[start][1] != (int)converted_matrix[end][1])
	{
		converted_matrix[start][1] += line_data->inc_y;
		y += line_data->inc_y;
		line_data->control -= line_data->dx;
		if (line_data->control < 0)
		{
			converted_matrix[start][0] += line_data->inc_x;
			x += line_data->inc_x;
			line_data->control += line_data->dy;
		}
		put_pixel(line_data->img, (int)converted_matrix[start][0],
			(int)converted_matrix[start][1], color);
	}
	converted_matrix[start][0] -= x;
	converted_matrix[start][1] -= y;
}

void	draw_line(mlx_image_t *img, float **converted_matrix, int start,
		int end, int color)
{
	t_data_draw_line	*line;

	line = new_line_data(img, converted_matrix, start, end);
	if (line->dx == 0)
		draw_vertical_line(line, converted_matrix, start, end, color);
	else if (line->dy == 0)
		draw_horizontal_line(line, converted_matrix, start, end, color);
	else
	{
		if (line->dx >= line->dy)
			draw_line_larger_x_axis(line, converted_matrix, start, end, color);
		else
			draw_line_larger_y_axis(line, converted_matrix, start, end, color);
	}
	free(line);
}
