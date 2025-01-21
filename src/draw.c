#include "../includes/fdf.h"

static void new_line(t_draw_line *line, t_references start, t_references end)
{
	line->d_x = ft_abs(end.x - start.x);
	line->d_y = ft_abs(end.y - start.y);
	line->control = 0;
	if (end.x > start.x)
		line->inc_x = 1;
	else
		line->inc_x = -1;
	if (end.y > start.y)
		line->inc_y = 1;
	else
		line->inc_y = -1;
}

void draw_line(t_fdf *fdf, t_references start, t_references end)
{
	t_draw_line line;

	new_line(&line, start, end);
	if (line.d_x == 0)
		axis_y(fdf, start, end);
	else if (line.d_y == 0)
		axis_x(fdf, start, end);
	else
	{
		if (line.d_x >= line.d_y)
			draw_diag_line_x(fdf, start, end, line);
		else
			draw_diag_line_y(fdf, start, end, line);
	}
}