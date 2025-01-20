#include "../includes/fdf.h"

static t_map	*new_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		ft_printf("Error alocate map");
	map->width = 0;
	map->height = 0;
	map->z_scale = 0;
	map->matrix = NULL;
	return (map);
}

static int	get_width(const char *map_name)
{
	int		fd;
	int		width;
	char	*line;
	char	**split_line;

	fd = open(map_name, O_RDONLY);
	line = get_next_line(fd);
	split_line = ft_split(line, ' ');
	width = 0;
	while ((split_line[width]) && (ft_strncmp(split_line[width], "\n",
				ft_strlen(split_line[width])) != 0))
		width++;
	free_split(split_line);
	free(line);
	if (!valid_map_width(fd, width))
		return (FALSE);
	return (width);
}

static int	get_height(const char *map_name)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(map_name, O_RDONLY);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

static void	get_matrix(t_map *map, const char *map_name)
{
	int		fd;
	char	*line;
	char	**split_line;
	int		height;

	fd = open(map_name, O_RDONLY);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		split_line = ft_split(line, ' ');
		fill_matrix(map, split_line, height);
		free_split(split_line);
		free(line);
		height++;
	}
}

t_map	*read_map(char *map_name, t_fdf *fdf)
{
	t_map	*map;

	map = new_map();
	map->height = get_height(map_name);
	map->width = get_width(map_name);
	if ((!map->width) || (map->width < 2) || (map->height < 2))
		clear_invalid_map(map, fdf);
	map->matrix = set_matrix(map->width, map->height);
	if (!map->matrix)
		ft_printf("Error alocate matrix");
	get_matrix(map, map_name);
	center_to_origin(map);
	return (map);
}
