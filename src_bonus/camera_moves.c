#include "../includes/fdf_bonus.h"

void move_up(t_map *map, float distance)
{
    t_map *current;

    current = map;
    while (current)
    {
        current->s_references->y -= distance;
        current = current->next;
    }
}

void move_down(t_map *map, float distance)
{
    t_map *current;

    current = map;
    while (current)
    {
        current->s_references->y += distance;
        current = current->next;
    }
}

void move_left(t_map *map, float distance)
{
    t_map *current;

    current = map;
    while (current)
    {
        current->s_references->x -= distance;
        current = current->next;
    }
}

void move_right(t_map *map, float distance)
{
    t_map *current;

    current = map;
    while (current)
    {
        current->s_references->x += distance;
        current = current->next;
    }
}