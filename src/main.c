#include "../includes/fdf.h"

static t_camera *set_camera(t_fdf *fdf);
static void keyboard_cmd(void *param);

void	init_fdf(t_fdf **fdf, char *map_name)
{
	*fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!(*fdf))
		ft_printf("Malloc failed");
	(*fdf)->map = NULL;
	(*fdf)->mlx = NULL;
	(*fdf)->img = NULL;
	(*fdf)->camera = NULL;
	(*fdf)->map = read_map(map_name, (*fdf));
	(*fdf)->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "\\[T]/", true);
	(*fdf)->img = mlx_new_image((*fdf)->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	(*fdf)->camera = set_camera((*fdf));
	mlx_image_to_window((*fdf)->mlx, (*fdf)->img, 0, 0);
}

static float get_scale(t_fdf *fdf)
{
	float	scale;
	float	scale_x;
	float	scale_y;

	scale_x = SCREEN_WIDTH / (float)fdf->map->width;
	scale_y = SCREEN_HEIGHT / (float)fdf->map->height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	return (scale / 1.75);
}

static t_camera *set_camera(t_fdf *fdf)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		ft_printf("Malloc failed");
	camera->x = fdf->map->width / 2;
	camera->y = fdf->map->height / 2;
	camera->z = 1;
	camera->scale = get_scale(fdf);
	if (fdf->map->z_scale <= 20)
		camera->z = 10;
	else if (fdf->map->z_scale > 720)
		camera->z = 0.5;
	return (camera);
}

static void keyboard_cmd(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if ((ac != 2) || (!validate_map(av[1])))
		ft_printf("Invalid map or map doesn't exist");
	init_fdf(&fdf, av[1]);
	mlx_loop_hook(fdf->mlx, keyboard_cmd, fdf);
	render(fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	kill_everything(fdf);
	return (0);
}
