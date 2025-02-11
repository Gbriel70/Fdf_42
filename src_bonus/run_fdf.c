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

#include "../includes/fdf_bonus.h"

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf *fdf = (t_fdf *)param;

	handle_movement_keys(keydata, fdf);
	handle_zoom_keys(keydata, fdf);
	handle_other_keys(keydata, fdf);
	rotate_keys(keydata, fdf);
}

static void	task_mlx(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &key_hook, fdf);
	mlx_mouse_hook(fdf->mlx, &mouse_hook, fdf);
	mlx_scroll_hook(fdf->mlx, &scroll_hook, fdf);
	mlx_cursor_hook(fdf->mlx, &cursor_hook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
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
	render(*fdf);
	task_mlx(*fdf);
	clean_data((*fdf)->s_map);
	free(*fdf);
}
