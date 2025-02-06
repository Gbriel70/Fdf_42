#include "../includes/fdf_bonus.h"

void	init_fdf(t_fdf **fdf, char *map_name)
{
	*fdf = malloc(sizeof(t_fdf));
	if (!(*fdf))
		return ;
	if (!create_map(*fdf, map_name))
	{
		*fdf = NULL;
		return ;
	}
	if (!init_mlx(*fdf))
	{
		*fdf = NULL;
		return ;
	}
	if (!create_img(*fdf))
	{
		*fdf = NULL;
		return ;
	}
	set_others(*fdf);
}

int create_map(t_fdf *fdf, char *map_name)
{
	fdf->s_map = NULL;
	fdf->s_map = read_map(map_name);
	if (!fdf->s_map)
	{
		print_return("File has no content or bad format", 1);
		free(fdf);
		return (0);
	}
	return (1);
}

int	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "\\[T]/", true);
	if (!fdf->mlx)
	{
		print_return("Mlx failed to initialize", 1);
		clean_data(fdf->s_map);
		free(fdf);
		return (0);
	}
	return (1);
}

int create_img(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!fdf->img)
	{
		print_return("Mlx failed to create image", 1);
		mlx_terminate(fdf->mlx);
		clean_data(fdf->s_map);
		free(fdf);
		return (0);
	}
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	if (!fdf->img)
	{
		print_return("Mlx failed to put image to window", 1);
		mlx_delete_image(fdf->mlx, fdf->img);
		mlx_terminate(fdf->mlx);
		clean_data(fdf->s_map);
		free(fdf);
		return (0);
	}
	return (1);
}

void set_others(t_fdf *fdf)
{
	fdf->mouse_x = 0;
	fdf->mouse_y = 0;
	fdf->mouse_pressed = 0;
}

