/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:22:25 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:22:28 by gcosta-m         ###   ########.fr       */
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

t_data_draw_line	*new_line_data(mlx_image_t *img, float **converted_matrix, int start, int end)
{
	t_data_draw_line	*line_data;

	line_data = (t_data_draw_line *)malloc(sizeof(t_data_draw_line));
	line_data->img = img;
	line_data->dx = ft_abs(converted_matrix[end][0] - converted_matrix[start][0]);
	line_data->dy = ft_abs(converted_matrix[end][1] - converted_matrix[start][1]);
	line_data->control = 0;
	if (converted_matrix[end][0] > converted_matrix[start][0])
		line_data->inc_x = 1;
	else
		line_data->inc_x = -1;
	if (converted_matrix[end][1] > converted_matrix[start][1])
		line_data->inc_y = 1;
	else
		line_data->inc_y = -1;
	return (line_data);
}

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	(void)mods;
	t_fdf *fdf = (t_fdf *)param;

	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		fdf->mouse_pressed = 1;
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		fdf->mouse_pressed = 0;
}

void scroll_hook(double x_delta, double y_delta, void *param)
{
	t_fdf *fdf = (t_fdf *)param;
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
    t_fdf *fdf = (t_fdf *)param;

    if (fdf->mouse_pressed)
    {
        int dx = xpos - fdf->mouse_x;
        int dy = ypos - fdf->mouse_y;

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