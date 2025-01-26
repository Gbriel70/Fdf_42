#include "../includes/fdf_bonus.h"

void draw_comands(mlx_t *mlx)
{
    mlx_put_string(mlx, "FDF COMMANDS!!", 10, 10);
    mlx_put_string(mlx, "Move: UP, DOWN, LEFT, RIGHT", 10, 30);
    mlx_put_string(mlx, "Zoom: Z, X", 10, 50);
    mlx_put_string(mlx, "Projection: P", 10, 70);
    mlx_put_string(mlx, "Exit: ESC", 10, 90);
    mlx_put_string(mlx, "Rotates: A, S, D", 10, 110);
    mlx_put_string(mlx, "Change color: R, G, B", 10, 130);
}
