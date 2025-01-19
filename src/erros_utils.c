#include "../includes/fdf.h"


void clear_invalid_map(t_fdf *fdf, t_map *map)
{
    free(map);
    free(fdf);
    print_error(1);
}

void print_error(int stage)
{
    if (stage == 1)
        ft_printf("\033[31;3mError, invalid map name :(\033[0m\n");
}