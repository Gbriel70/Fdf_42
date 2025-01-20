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

t_references **set_matrix(int width, int height)
{
    t_references **matrix;
    int i;
    int j;

    matrix = (t_references **)malloc(sizeof(t_references *) * height);
    if (!matrix)
        ft_printf("Error alocate matrix");
    i = 0;
    while (i < height)
    {
        matrix[i] = (t_references *)malloc(sizeof(t_references) * width);
        if (!matrix[i])
            ft_printf("Error alocate matrix");
        j = 0;
        while (j < width)
        {
            matrix[i][j].x = 0;
            matrix[i][j].y = 0;
            matrix[i][j].z = 0;
            matrix[i][j].color = 0;
            j++;
        }
        i++;
    }
    return (matrix);
}

void fill_matrix(t_map *map, char **split_line, int height)
{
    int index;

    index = 0;
    while (index < map->width)
    {
        map->matrix[height][index].x = (float)index;
        map->matrix[height][index].y = (float)height;
        map->matrix[height][index].z = (float)ft_atoi(split_line[index]);
        if (map->matrix[height][index].z > map->z_scale)
            map->z_scale = map->matrix[height][index].z;
        if (ft_strchr(split_line[index], ','))
            map->matrix[height][index].color = ft_atoi_base(\
					ft_strchr(split_line[index], 'x') + 1, HEXA_BASE);
        else
            map->matrix[height][index].color = 0xFFFFFF;
        index++;
    }
}

void	center_to_origin(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->matrix[y][x].x -= map->width / 2;
			map->matrix[y][x].y -= map->height / 2;
			x++;
		}
		y++;
	}
}
