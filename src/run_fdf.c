/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:23:49 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:23:52 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	key_hook(mlx_key_data_t keydata, void *mlx)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

static void	task_mlx(mlx_t *mlx)
{
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return ;
}

void	run_fdf(t_fdf **fdf, char *map_name)
{
	init_fdf(fdf, map_name);
	if (!(*fdf) || !(*fdf)->s_map || !(*fdf)->mlx || !(*fdf)->img)
	{
		free(*fdf);
		return ;
	}
	render((*fdf)->s_map, (*fdf)->img);
	task_mlx((*fdf)->mlx);
	clean_data((*fdf)->s_map);
	free(*fdf);
}
