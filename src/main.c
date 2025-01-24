#include "../includes/fdf.h"

int main(int ac, char **av)
{
	t_fdf 	*fdf;

	fdf = NULL;

	if (ac != 2 || check_map_format(av[1]))
		return (1);
	run_fdf(&fdf, av[1]);
	return (0);
}
