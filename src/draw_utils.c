#include "../includes/fdf.h"

static void pixel_put(t_fdf *fdf, int x, int y, uint32_t color)
{
	if (x <= 0 || x >= SCREEN_WIDTH || y <= 0 || y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(fdf->img, x, y, color);
}

void	axis_y(t_fdf *fdf, t_references start, t_references end)
{
	if (end.y > start.y)
	{
		while ((int)start.y != (int)end.y)
		{
			start.y++;
			pixel_put(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
	else
	{
		while ((int)start.y != (int)end.y)
		{
			start.y--;
			pixel_put(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
}

void	axis_x(t_fdf *fdf, t_references start, t_references end)
{
	if (end.x > start.x)
	{
		while ((int)start.x != (int)end.x)
		{
			start.x++;
			pixel_put(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
	else
	{
		while ((int)start.x != (int)end.x)
		{
			start.x--;
			pixel_put(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
}

void	draw_diag_line_x(t_fdf *fdf, t_references start, t_references end, t_draw_line line)
{
	line.control = line.d_x / 2;
	pixel_put(fdf, (int)start.x, (int)start.y, start.color);
	while ((int)start.x != (int)end.x)
	{
		start.x += line.inc_x;
		line.control -= line.d_y;
		if (line.control < 0)
		{
			start.y += line.inc_y;
			line.control += line.d_x;
		}
		pixel_put(fdf, (int)start.x, (int)start.y, start.color);
	}
}

void	draw_diag_line_y(t_fdf *fdf, t_references start, t_references end, t_draw_line line)
{
	line.control = line.d_y / 2;
	pixel_put(fdf, (int)start.x, (int)start.y, start.color);
	while ((int)start.y != (int)end.y)
	{
		start.y += line.inc_y;
		line.control -= line.d_x;
		if (line.control < 0)
		{
			start.x += line.inc_x;
			line.control += line.d_y;
		}
		pixel_put(fdf, (int)start.x, (int)start.y, start.color);
	}
}
