#include "../includes/fdf.h"

short	valid_map_width(int fd, int width)
{
	char	*line;
	char	**split_line;
	int		temp_width;
	short	valid;

	temp_width = 0;
	valid = true;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		while (split_line[temp_width] && split_line[temp_width][0] != '\n')
			temp_width++;
		if (temp_width != width)
			valid = false;
		temp_width = 0;
		free(line);
		free_split(split_line);
	}
	close(fd);
	get_next_line(-1);
	return (valid);
}

t_references	**set_matrix(int width, int height)
{
	t_references	**matrix;

	matrix = malloc(sizeof(t_references *) * height);
	if (!matrix)
		ft_printf("Error alocate matrix");
	while (height--)
	{
		matrix[height] = ft_calloc(width, sizeof(t_references));
		if (!matrix[height])
			ft_printf("Error alocate matrix");
	}
	return (matrix);
}

void	fill_matrix(t_map *map, char **split_line, int height)
{
	int	index;
	char *color;

	index = 0;
	while (index < map->width)
	{
		map->matrix[height][index].x = (float)index;
		map->matrix[height][index].y = (float)height;
		map->matrix[height][index].z = (float)(ft_atoi(split_line[index]));
		if (map->matrix[height][index].z > map->z_scale)
			map->z_scale = map->matrix[height][index].z;
		color = ft_strchr(split_line[index], ',');
		if (color)
			map->matrix[height][index].color = put_alpha(ft_hex_to_int(color + 1));
		else
		{
			if (map->matrix[height][index].z <= 0)
				map->matrix[height][index].color = 0x4ea8de;
			else
				map->matrix[height][index].color = 0xfffb6f92;
		}
		index++;
	}
}

void	center_to_origin(t_map *map)
{
	unsigned short	x;
	unsigned short	y;

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
