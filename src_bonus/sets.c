/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:22:25 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 11:18:07 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	background(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(img, x, y, BACKGROUND_COLOR);
			x++;
		}
		x = 0;
		y++;
	}
}

t_data_draw_line	*new_line_data(mlx_image_t *img, t_point start, t_point end)
{
	t_data_draw_line	*line;

	line = (t_data_draw_line *)malloc(sizeof(t_data_draw_line));
	if (!line)
		return (NULL);
	line->dx = abs((int)(end.x - start.x));
	line->dy = abs((int)(end.y - start.y));
	if (start.x < end.x)
		line->inc_x = 1;
	else
		line->inc_x = -1;
	if (start.y < end.y)
		line->inc_y = 1;
	else
		line->inc_y = -1;
	line->img = img;
	return (line);
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_fdf	*fdf;

	(void)mods;
	fdf = (t_fdf *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		fdf->mouse_pressed = 1;
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		fdf->mouse_pressed = 0;
}

void	scroll_hook(double x_delta, double y_delta, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	(void)x_delta;
	if (y_delta > 0)
	{
		zoom_in(fdf->s_map, 1.1);
		render(fdf);
	}
	else if (y_delta < 0)
	{
		zoom_out(fdf->s_map, 1.1);
		render(fdf);
	}
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_fdf	*fdf;
	int		dx;
	int		dy;

	fdf = (t_fdf *)param;
	if (fdf->mouse_pressed)
	{
		dx = xpos - fdf->mouse_x;
		dy = ypos - fdf->mouse_y;
		if (dx > 0)
			move_right(fdf->s_map, dx);
		else if (dx < 0)
			move_left(fdf->s_map, -dx);
		if (dy > 0)
			move_down(fdf->s_map, dy);
		else if (dy < 0)
			move_up(fdf->s_map, -dy);
		render(fdf);
	}
	fdf->mouse_x = xpos;
	fdf->mouse_y = ypos;
}
