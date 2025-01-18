#include "../includes/fdf.h"

static uint32_t	put_alpha(uint32_t color)
{
	uint32_t		new;
	unsigned char	*ptr;

	new = color << 8;
	ptr = (unsigned char *)&new;
	*ptr = 255;
	return (new);
}

static int	process_line(t_map *map, char **div_line, int i)
{
	int		j;
	char	*color;

	j = 0;
	while (j < map->width)
	{
		map->matrix[i][j].x = (float)j;
		map->matrix[i][j].y = (float)i;
		map->matrix[i][j].z = (float)(ft_atoi(div_line[j]));
		if (map->matrix[i][j].z > map->z_scale)
			map->z_scale = map->matrix[i][j].z;
		color = ft_strchr(div_line[j], ',');
		if (color)
			map->matrix[i][j].color = put_alpha(ft_hex_to_int(color + 1));
		else
		{
			if (map->matrix[i][j].z <= 0)
				map->matrix[i][j].color = put_alpha(0x3333FF);
			else
				map->matrix[i][j].color = put_alpha(0xFF3333);
		}
		j++;
	}
	return (0);
}

static int	process_map_line(t_map *map, char *line, int line_i)
{
	char	**div_line;

	div_line = ft_split(line, ' ');
	if (!div_line)
		handle_error("Malloc failed", STAGE_MAP, map);
	if (process_line(map, div_line, line_i) == -1)
	{
		ft_free_array(div_line);
		handle_error("Process line failed", STAGE_MAP, map);
		return (0);
	}
	ft_free_array(div_line);
	return (1);
}	

void	convert_map(t_map *map, char *n_map)
{
	int		line_i;
	int		fd;
	char	*line;

	fd = open(n_map, O_RDONLY);
	if (fd < 0)
        handle_error("Error opening file", STAGE_MAP, map);
	line_i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!process_map_line(map, line, line_i))
		{
			free(line);
			break ;
		}
		free(line);
		line_i++;
	}
	close (fd);
}

void	center_map(t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < (unsigned int)map->height)
	{
		x = 0;
		while (x < (unsigned int)map->width)
		{
			map->matrix[y][x].x -= map->width / 2;
			map->matrix[y][x].y -= map->height / 2;
			x++;
		}
		y++;
	}
}
