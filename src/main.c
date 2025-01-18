#include "../includes/fdf.h"

static t_camera *cam_settings(t_fdf *fdf);

void init_fdf(t_fdf **fdf, char *map_name)
{
   *fdf = (t_fdf *)malloc(sizeof(t_fdf));
   if (!(*fdf))
      handle_error("Malloc failed", STAGE_NONE, NULL);
   (*fdf)->map = map_read(map_name);
   if (!(*fdf)->map)
      handle_error("Map read failed", STAGE_NONE, NULL);
   (*fdf)->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "FdF", 1);
   if (!(*fdf)->mlx)
      handle_error("Mlx init failed", STAGE_MLX, *fdf);
   (*fdf)->img = mlx_new_image((*fdf)->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
   if (!(*fdf)->img)
      handle_error("Mlx new image failed", STAGE_MLX, *fdf);
   (*fdf)->camera = cam_settings(*fdf);
   mlx_image_to_window((*fdf)->mlx, (*fdf)->img, 0, 0);
}

static float get_scale(t_fdf *fdf)
{
   float scale;
   float scale_x;
   float scale_y;

   scale_x = SCREEN_WIDTH / (float)fdf->map->width;
   scale_y = SCREEN_HEIGHT / (float)fdf->map->height;
   if (scale_x < scale_y)
      scale = scale_x;
   else
      scale = scale_y;
   return (scale / 1.75);
}

static t_camera *cam_settings(t_fdf *fdf)
{
   t_camera *camera;

   camera = (t_camera *)malloc(sizeof(t_camera));
   if (!camera)
      handle_error("Malloc failed", STAGE_NONE, NULL);
   camera->scale = get_scale(fdf);
   camera->x = (SCREEN_WIDTH / 2);
   camera->y = (SCREEN_HEIGHT / 2);
   camera->z = 1;
   if (fdf->map->z_scale <= 20)
      camera->z = 10;
   else if (fdf->map->z_scale > 720)
      camera->z = 0.05;
   return (camera);
}

void keyboard_hook(void *param)
{
   t_fdf *fdf;

   fdf = (t_fdf *)param;
   if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
      mlx_close_window(fdf->mlx);
}


int main(int ac, char **av)
{

   t_fdf *fdf;

   if ((ac != 2) || (!validate_map(av[1])))
      handle_error("Invalid map or map doesn't exist", STAGE_NONE, NULL);
   init_fdf(&fdf, av[1]);
   mlx_loop_hook(fdf->mlx, keyboard_hook, fdf);
   mlx_loop(fdf->mlx);
   mlx_terminate(fdf->mlx);
   cleanup_resources(fdf);
   return 0;
}
