/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:20:47 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:20:50 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	fdf = NULL;
	if (ac != 2 || check_map_format(av[1]))
		return (1);
	run_fdf(&fdf, av[1]);
	return (0);
}
