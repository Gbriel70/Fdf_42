/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_moves.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:20:41 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 11:20:43 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	handle_movement_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		move_up(fdf->s_map, 10, fdf->projection);
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		move_down(fdf->s_map, 10, fdf->projection);
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		move_left(fdf->s_map, 10, fdf->projection);
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		move_right(fdf->s_map, 10, fdf->projection);
		render(fdf);
	}
}

void	handle_zoom_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
	{
		zoom_in(fdf->s_map, 1.1);
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
	{
		zoom_out(fdf->s_map, 1.1);
		render(fdf);
	}
}

void	handle_other_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(fdf->mlx);
	}
	else if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		fdf->projection = 1;
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		fdf->projection = 2;
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
	{
		fdf->projection = 0;
		render(fdf);
	}
}

void	rotate_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		rotate_x(fdf->s_map, M_PI / 18);
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		rotate_y(fdf->s_map, M_PI / 18);
		render(fdf);
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		rotate_z(fdf->s_map, M_PI / 18);
		render(fdf);
	}
}
