#include "../includes/fdf.h"

static void background(t_fdf *fdf, uint32_t color)
{
	uint32_t *pixel;
	uint32_t i;

	pixel = (uint32_t *)fdf->img->pixels;
	i = fdf->img->height * fdf->img->width;
	while (i--)
		pixel[i] = color;
}

static void set(t_fdf *fdf, t_references start, t_references end)
{
	scale(fdf, &start, &end);
	isometry(fdf, &start, &end);
	centralize(fdf, &start, &end);
	draw_line(fdf, start, end);
}

void render(t_fdf *fdf)
{
	int x;
	int y;

	background(fdf, BACKGROUND_COLOR);
	y = 0;
	while (y + 1 <= fdf->map->height)
	{
		x = 0;
		while (x + 1 <= fdf->map->width)
		{
			if (x + 1 < fdf->map->width)
				set(fdf, fdf->map->matrix[y][x], fdf->map->matrix[y][x + 1]);
			if (y + 1 < fdf->map->height)
				set(fdf, fdf->map->matrix[y][x], fdf->map->matrix[y + 1][x]);
			x++;
		}
		y++;
	}
}
