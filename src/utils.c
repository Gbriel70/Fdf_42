#include "../includes/fdf.h"

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
}

void clean_data(t_map *s_map)
{
	t_map *remove;

	while (s_map)
	{
		remove = s_map;
		s_map = s_map->next;
		if (remove->s_references != NULL)
		{
			free(remove->s_references);
			remove->s_references = NULL;
		}
		free(remove);
	}
}

void clean_matrix(float **map_matrix)
{
	int x;

	x = 0;
	while (map_matrix[x] != NULL)
		free(map_matrix[x++]);
	free(map_matrix);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_data_draw_line *new_line_data(mlx_image_t *img, float **converted_matrix, int start, int end)
{
	t_data_draw_line *line_data;

	line_data = (t_data_draw_line *)malloc(sizeof(t_data_draw_line));
	line_data->img = img;
	line_data->dx = ft_abs(converted_matrix[end][0] - converted_matrix[start][0]);
	line_data->dy = ft_abs(converted_matrix[end][1] - converted_matrix[start][1]);
	line_data->control = 0;
	if (converted_matrix[end][0] > converted_matrix[start][0])
		line_data->inc_x = 1;
	else
		line_data->inc_x = -1;
	if (converted_matrix[end][1] > converted_matrix[start][1])
		line_data->inc_y = 1;
	else
		line_data->inc_y = -1;
	return (line_data);
}
