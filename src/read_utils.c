#include "../includes/fdf.h"

static t_map *new_map(void)
{
    t_map   *map;

    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        handle_error("Malloc failed", STAGE_NONE, NULL);
    map->width = 0;
    map->height = 0;
    map->z_scale = 0;
    map->matrix = NULL;
    return (map);
}

static int recive_width(char *map_name)
{
    int     fd;
    int     count;
    char    *line;
    char    **split_line;

    fd = open(map_name, O_RDONLY);
    if (fd < 0)
        handle_error("Error opening file", STAGE_NONE, NULL);
    line = get_next_line(fd);
    if (!line)
        return (close(fd), -1);
    split_line = ft_split(line, ' ');
    free(line);
    if (!split_line)
        return (close(fd), -1);
    count = 0;
    while (split_line[count] && split_line[count][0] != '\n')
        count++;
    ft_free_array(split_line);
    close(fd);
    return (count);
}

static int recive_height(char *map_name)
{
    int     fd;
    int     height;
    char    *line;

    fd = open(map_name, O_RDONLY);
    if (fd < 0)
        handle_error("Error opening file", STAGE_NONE, NULL);
    height = 0;
    while ((line = get_next_line(fd)))
    {
        height++;
        free(line);
    }
    close(fd);
    return (height);
}

static void fill_matrix(t_map *map, char *map_name)
{
    int     fd;
    char    *line;
    char    **split_line;
    int     i;
    int     j;

    fd = open(map_name, O_RDONLY);
    i = 0;
    while ((line = get_next_line(fd)) && i < map->height)
    {
        split_line = ft_split(line, ' ');
        if (!split_line)
            handle_error("Split failed", STAGE_MAP, map);
        j = 0;
        while (split_line[j] && j < map->width)
        {
            map->matrix[i][j] = ft_atoi(split_line[j]);
            j++;
        }
        ft_free_array(split_line);
        free(line);
        i++;
    }
    close(fd);   
}

t_map *map_read(char *map_name)
{
    t_map   *map;
    
    map = new_map();
    if (!map)
        handle_error("Malloc failed", STAGE_NONE, NULL);
    map->width = recive_width(map_name);
    map->height = recive_height(map_name);
    if (map->width <= 0 || map->height <= 0)
        handle_error("Invalid map", STAGE_MAP, map);
    map->matrix = alloc_matrix(map->height, map->width);
    if (!map->matrix)
        handle_error("Malloc failed", STAGE_MAP, map);
    fill_matrix(map, map_name);
    return (map);
}
