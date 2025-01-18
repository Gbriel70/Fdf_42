#include "../includes/fdf.h"

static void cleanup_matrix(t_references **matrix, int height)
{
    int i;

    if (!matrix)
        return ;
    i = -1;
    while (++i < height)
    {
        if (matrix[i])
            free(matrix[i]);
    }
    free(matrix);
}

static void cleanup_mlx(mlx_t *mlx, mlx_image_t *img)
{
    if (img)
        mlx_delete_image(mlx, img);
    if (mlx)
    {
        mlx_terminate(mlx);
        free(mlx);
    }
}

static void cleanup_map(t_map *map)
{
    if (map)
    {
        cleanup_matrix(map->matrix, map->height);
        free(map);
    }
}

void cleanup_resources(t_fdf *fdf)
{
    if (fdf)
    {
        cleanup_map(fdf->map);
        if (fdf->camera)
            free(fdf->camera);
        cleanup_mlx(fdf->mlx, fdf->img);
        free(fdf);
    }
}

void handle_error(char *error_message, int stage, void *ptr)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
    perror(error_message);

    if (stage == STAGE_MAP)
    {
        if (ptr)
            cleanup_map((t_map *)ptr);
    }
    else if (stage == STAGE_MATRIX)
    {
        if (ptr)
            cleanup_matrix(((t_map *)ptr)->matrix, ((t_map *)ptr)->height);
    }
    else if (stage == STAGE_MLX)
    {
        if (ptr)
            cleanup_mlx(((t_fdf *)ptr)->mlx, ((t_fdf *)ptr)->img);
    }
    else if (stage == STAGE_FULL)
    {
        if (ptr)
            cleanup_resources((t_fdf *)ptr);
    }
    exit(1);
}