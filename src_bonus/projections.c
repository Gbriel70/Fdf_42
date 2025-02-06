#include "../includes/fdf_bonus.h"

void parallel_projection(t_map *s_map, t_point *point)
{
    point->x = s_map->s_references->x;
    point->y = s_map->s_references->y;
    point->color = s_map->s_references->color;
}

void isometric_projection(t_map *s_map, t_point *point)
{
    point->x = (s_map->s_references->x - s_map->s_references->y) * cos(COS_30);
    point->y = (s_map->s_references->x + s_map->s_references->y) * sin(SIN_30) - 0.15 * s_map->s_references->z;
    point->color = s_map->s_references->color;
}