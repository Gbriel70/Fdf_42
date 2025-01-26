#include "../includes/fdf_bonus.h"

void parallel_projection(t_map *s_map, float **map_matrix, int x)
{
    map_matrix[x][0] = s_map->s_references->x;
    map_matrix[x][1] = s_map->s_references->y;
}

void isometric_projection(t_map *s_map, float **map_matrix, int x)
{
    map_matrix[x][0] = (s_map->s_references->x - s_map->s_references->y) * cos(COS_30);
    map_matrix[x][1] = (s_map->s_references->x + s_map->s_references->y) * sin(SIN_30) - 0.15 * s_map->s_references->z;
}