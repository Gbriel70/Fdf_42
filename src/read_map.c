#include "../includes/fdf.h"

static t_map *new_map(void)
{
    t_map *map;

    map = malloc(sizeof(t_map));
    if (!map)
        handle_error("Malloc failed", STAGE_NONE, NULL);
    map->width = 0;
    map->height = 0;
    map->z_scale = 0;
    map->matrix = NULL;
    return (map);
}

static int get_width(const char *map_name)
{
    int fd;
    int count;
    char *line;
    char **split_line;

    fd = open(map_name, O_RDONLY);
    if (fd < 0)
        return(handle_error("Error opening file", STAGE_NONE, NULL), -1);
    line = get_next_line(fd);
    if (!line)
        return(close(fd), -1);
    split_line = ft_split(line, ' ');
    free(line);
    if (!split_line)
        return(close(fd), -1);
    count = 0;
    while (split_line[count] && split_line[count][0] != '\n')
        count++;
    free_split(split_line);
    close(fd);
    return (count);
}

static int get_height(const char *map_name)
{
    int fd;
    int height;
    char *line;

    fd = open(map_name, O_RDONLY);
    if (fd < 0)
        return(handle_error("Error opening file", STAGE_NONE, NULL), -1);
    height = 0;
    line = get_next_line(fd);
    if (!line)
        return(close(fd), -1);
    while (line)
    {
        height++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (height);
}

static void check_line_consistency(const char *map_name, int width)
{
    int fd;
    char *line;
    char **split_line;
    int count;

    fd = open(map_name, O_RDONLY);
    if (fd < 0)
        handle_error("Error opening file", STAGE_NONE, NULL);
    line = get_next_line(fd);
    while (line)
    {
        split_line = ft_split(line, ' ');
        free(line);
        if (!split_line)
            handle_error("Error splitting line", STAGE_MAP, NULL);
        count = 0;
        while (split_line[count] && split_line[count][0] != '\n')
            ft_printf("count iteration v: %d\n" ,count++);
        free_split(split_line);
        if (count != width)
            handle_error("Inconsistent map width", STAGE_MAP, NULL);
        line = get_next_line(fd);
    }
    close(fd);
}

t_map *read_map(char *map_name)
{
    t_map *map;

    map = new_map();
    map->width = get_width(map_name);
    map->height = get_height(map_name);
    ft_printf("Map width: %d\n", map->width);
    ft_printf("Map height: %d\n", map->height);
    if (map->width < 2 || map->height < 2)
        handle_error("Map format error", STAGE_MAP, map);
    check_line_consistency(map_name, map->width);
    return (map);
}