#include "../includes/fdf.h"

static float **get_map_matrix(t_map *s_map)
{
	float **map_matrix;
	int x;
	int y;

	y = 0;
	x = 0;
	map_matrix = (float **)malloc(sizeof(float *) * (s_map->height * s_map->width + 2));
	while (s_map != NULL)
	{
		y = 0;
		map_matrix[x] = malloc(sizeof(float) * 2);
		map_matrix[x][y] = (s_map->s_references->x - s_map->s_references->y) * cos(COS_30);
		y++;
		map_matrix[x][y] = (s_map->s_references->x + s_map->s_references->y) * sin(SIN_30) - 0.15 * s_map->s_references->z;
		x++;
		s_map = s_map->next;
	}
	map_matrix[x] = NULL;
	return (map_matrix);
}

static float **convert_matrix(t_map *s_map, float **map_matrix)
{
	float **converted_matrix;
	t_matrix_dimensions *s_matrix_dimensions;

	s_matrix_dimensions = get_matrix_dimensions(map_matrix, s_map);
	get_map_scale(s_map);
	converted_matrix = scale_dimension_matrix(s_map, map_matrix, s_matrix_dimensions);
	return (converted_matrix);
}

static void draw_map(t_map *s_map, mlx_image_t *img, float **converted_matrix)
{
	int x;
	int width;
	int height;

	x = 0;
	width = s_map->width;
	height = s_map->height;
	while (s_map)
	{
		if ((x + 1) % width != 0)
			draw_line(img, converted_matrix, x, x + 1);
		if (x < (height - 1) * width)
			draw_line(img, converted_matrix, x, x + width);
		x++;
		s_map = s_map->next;
	}
	clean_matrix(converted_matrix);
}

void render(t_map *s_map, mlx_image_t *img)
{
	float **map_matrix;
	float **converted_matrix;

	background(img);
	map_matrix = get_map_matrix(s_map);
	converted_matrix = convert_matrix(s_map, map_matrix);
	draw_map(s_map, img, converted_matrix);
	return ;
}
