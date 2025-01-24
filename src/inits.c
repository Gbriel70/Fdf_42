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

#include "../includes/fdf.h"

void	init_fdf(t_fdf **fdf, char *map_name)
{
	*fdf = malloc(sizeof(t_fdf));
	if (!(*fdf))
		print_return("Malloc failed", 1);
	(*fdf)->s_map = NULL;
	(*fdf)->s_map = read_map(map_name);
	if (!(*fdf)->s_map)
	{
		print_return("File has no content or bad format", 1);
		return ;
	}
	(*fdf)->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "\\[T]/", true);
	if (!(*fdf)->mlx)
	{
		print_return("Mlx failed to initialize", 1);
	}
	(*fdf)->img = mlx_new_image((*fdf)->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!(*fdf)->img)
	{
		print_return("Mlx failed to create image", 1);
	}
	mlx_image_to_window((*fdf)->mlx, (*fdf)->img, 0, 0);
	if (!(*fdf)->img)
		print_return("Mlx failed to put image to window", 1);
}

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

void	put_pixel(mlx_image_t *img, int start, int end, int color)
{
	if (start <= 0 || end <= 0 || start >= SCREEN_WIDTH || end >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(img, start, end, color);
}
