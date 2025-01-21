#include "../includes/fdf.h"

void scale(t_fdf *fdf, t_references *start, t_references *end)
{
	start->x *= fdf->camera->scale;
	start->y *= fdf->camera->scale;
	end->x *= fdf->camera->scale;
	end->y *= fdf->camera->scale;
}

void isometry(t_fdf *fdf, t_references *start, t_references *end)
{
	t_references n_start;
	t_references n_end;

	n_start.x = (start->x - start->y) * cos(X_AXIS_ANGLE_ROTATION_RADIUS);
	n_start.y = (start->x + start->y) * sin(Z_AXIS_ANGLE_ROTATION_RADIUS) - (start->z * fdf->camera->z);
	n_end.x = (end->x - end->y) * cos(X_AXIS_ANGLE_ROTATION_RADIUS);
	n_end.y = (end->x - end->y) * sin(Z_AXIS_ANGLE_ROTATION_RADIUS) - (end->z * fdf->camera->z);
	start->x = n_start.x;
	start->y = n_start.y;
	end->x = n_end.x;
	end->y = n_end.y;
}

void centralize(t_fdf *fdf, t_references *start, t_references *end)
{
	start->x += fdf->camera->x;
	start->y += fdf->camera->y;
	end->x += fdf->camera->x;
	end->y += fdf->camera->y;
}