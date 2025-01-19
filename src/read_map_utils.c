#include "../includes/fdf.h"

short   valid_map_width(int fd, int width)
{
    char *line;
    char **split_line;
    int temp_width;
    short valid;

    temp_width = 0;
    valid = TRUE;
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        split_line = ft_split(line, ' ');
        while ((split_line[temp_width]) && \
                (ft_strncmp(split_line[temp_width], "\n", \
                ft_strlen(split_line[temp_width])) != 0))
            temp_width++;
        if (temp_width != width)
            valid = FALSE;
        temp_width = 0;
        free_split(split_line);
        free(line);
    }
    close(fd);
    return (valid);
}
