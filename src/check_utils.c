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
    if (fd < 0)
        return (FALSE);
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        return (FALSE);
    }
    free(line);
    close(fd);
    return (TRUE);
}
