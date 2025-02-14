/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:12:04 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/12 11:13:13 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

int	parse_color(char *token)
{
	char	*comma;

	comma = ft_strchr(token, ',');
	if (comma)
		return (ft_atoi_base(comma + 1, 16));
	return (0xFF00FF);
}

int	parse_height(char *token)
{
	char	*comma;
	int		height;

	comma = ft_strchr(token, ',');
	if (comma)
		*comma = '\0';
	height = ft_atoi(token);
	if (comma)
		*comma = ',';
	return (height);
}
