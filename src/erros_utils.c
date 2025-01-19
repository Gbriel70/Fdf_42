#include "../includes/fdf.h"


void cleanup_resources(t_fdf *fdf, int stage)
{
    (void)fdf;

    if (stage >= STAGE_MAP)
    {
        ft_printf("Cleaning map resources\n");
    }
    return ;
}

void handle_error(char *error_message, int stage, void *ptr)
{
    ft_printf("Error: %s\n", error_message);
    cleanup_resources((t_fdf *)ptr, stage);
    exit(EXIT_FAILURE);
}
