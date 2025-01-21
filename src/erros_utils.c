#include "../includes/fdf.h"

static void	clear_matrix(t_references **matrix, int height)
{
	int	index;

	index = 0;
	while (index < height)
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
}

void	kill_everything(t_fdf *fdf)
{
	clear_matrix(fdf->map->matrix, fdf->map->height);
	free(fdf->map);
	free(fdf->camera);
	free(fdf);
}

void	clear_invalid_map(t_map *map, t_fdf *fdf)
{
	free(map);
	free(fdf);
	print_error(1);
}

void	print_error(int stage)
{
	if (stage == 1)
		ft_printf("\033[31;3mError, invalid map!!!\033[0m\n");
	exit(stage);
}