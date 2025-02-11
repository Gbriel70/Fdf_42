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

/*void oblique_projection(t_map *s_map, float **map_matrix, int x)
{
    float angle = M_PI / 4; // 45 degrees
    float scale = 0.5; // Scale factor for the z-axis
    map_matrix[x][0] = s_map->s_references->x + scale * s_map->s_references->z * cos(angle);
    map_matrix[x][1] = s_map->s_references->y + scale * s_map->s_references->z * sin(angle);
}*/

/*void dimetric_projection(t_map *s_map, float **map_matrix, int x)
{
    float angle_x = M_PI / 6; // 30 degrees
    float angle_y = M_PI / 4; // 45 degrees
    map_matrix[x][0] = s_map->s_references->x * cos(angle_x) - s_map->s_references->y * cos(angle_y);
    map_matrix[x][1] = s_map->s_references->x * sin(angle_x) + s_map->s_references->y * sin(angle_y) - s_map->s_references->z;
}*/

/*void spherical_projection(t_map *s_map, float **map_matrix, int x)
{
    float r = sqrt(s_map->s_references->x * s_map->s_references->x +
                   s_map->s_references->y * s_map->s_references->y +
                   s_map->s_references->z * s_map->s_references->z);
    float theta = atan2(s_map->s_references->y, s_map->s_references->x);
    float phi = acos(s_map->s_references->z / r);
    map_matrix[x][0] = r * sin(phi) * cos(theta);
    map_matrix[x][1] = r * sin(phi) * sin(theta);
}*/

/*void cylindrical_projection(t_map *s_map, float **map_matrix, int x)
{
    float theta = atan2(s_map->s_references->y, s_map->s_references->x);
    float h = s_map->s_references->z;
    map_matrix[x][0] = theta * 100; // Ajuste a escala conforme necessário
    map_matrix[x][1] = h;
}*/

void trimetric_projection(t_map *s_map, float **map_matrix, int x)
{
    float angle_x = M_PI / 6; // 30 degrees
    float angle_y = M_PI / 6; // 30 degrees
    float angle_z = M_PI / 6; // 30 degrees
    map_matrix[x][0] = s_map->s_references->x * cos(angle_x) - s_map->s_references->y * cos(angle_y);
    map_matrix[x][1] = s_map->s_references->x * sin(angle_x) + s_map->s_references->y * sin(angle_y) - s_map->s_references->z * cos(angle_z);
}
