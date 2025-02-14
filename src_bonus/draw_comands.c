/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_comands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:13:29 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 11:13:30 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	draw_comands(mlx_t *mlx)
{
	mlx_put_string(mlx, "FDF COMMANDS!!", 10, 10);
	mlx_put_string(mlx, "Move: UP, DOWN, LEFT, RIGHT", 10, 30);
	mlx_put_string(mlx, "Zoom: Z, X", 10, 50);
	mlx_put_string(mlx, "Projection: 1, 2, 3", 10, 70);
	mlx_put_string(mlx, "Exit: ESC", 10, 90);
	mlx_put_string(mlx, "Rotates: A, S, D", 10, 110);
}
