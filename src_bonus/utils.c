/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:24:01 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/13 11:15:42 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	clean_data(t_map *s_map)
{
	t_map	*remove;

	while (s_map)
	{
		remove = s_map;
		s_map = s_map->next;
		if (remove->s_references != NULL)
		{
			free(remove->s_references);
			remove->s_references = NULL;
		}
		free(remove);
	}
}

void	clean_matrix(float **map_matrix)
{
	int	x;

	x = 0;
	if (!map_matrix)
		return ;
	while (map_matrix[x] != NULL)
	{
		free(map_matrix[x]);
		x++;
	}
	free(map_matrix);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	int	rgba_color;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		rgba_color = (color << 8) | 0xFF;
		mlx_put_pixel(img, x, y, rgba_color);
	}
}
