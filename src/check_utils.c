# include "../includes/fdf.h"

short validate_map(char *map_name)
{
    size_t  l;
    int     fd;
    char    *line;

    l = ft_strlen(map_name);
    if (!ft_strnstr(map_name, ".fdf", l))
        return (FALSE);
    fd = open(map_name, O_RDONLY);
    line = get_next_line(fd);
    if (!line)
        return (FALSE);
    if (fd < 0)
    {
        close(fd);
        return (FALSE);
    }
    free(line);
    close(fd);
    return (TRUE);
}

short	validate_map_init(t_map *map)
{
    int	i;

    if (!map)
        return (FALSE);
    if (!map->matrix)
        return (FALSE);
    if (map->width <= 0 || map->height <= 0)
        return (FALSE);
    i = 0;
    while (i < map->height)
    {
        if (!map->matrix[i])
            return (FALSE);
        i++;
    }
    return (TRUE);
}