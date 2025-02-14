/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:21:30 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:21:33 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static short	has_fdf_extension(const char *map_name)
{
	int			l;
	const char	*dot = ft_strrchr(map_name, '.');

	l = ft_strlen(map_name);
	if (!dot || dot == map_name)
		return (FALSE);
	return (ft_strncmp(dot, ".fdf", l) == 0);
}

static short	is_file_acessible(const char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

int	check_map_format(const char *map_name)
{
	if (!has_fdf_extension(map_name))
		print_return("File has no .fdf extension", 1);
	if (!is_file_acessible(map_name))
		print_return("File does not exist or is not accessible or is empty", 1);
	return (0);
}

int	print_return(char *message, int return_value)
{
	ft_printf("\033[31;3m%s\033[0m\n", message);
	return (return_value);
}
