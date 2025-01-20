#include "../includes/fdf.h"

void init_fdf(t_fdf **fdf, char *map_name)
{
   *fdf = (t_fdf *)malloc(sizeof(t_fdf));
   if (!(*fdf))
      ft_printf("Malloc failed");
   (*fdf)->map = NULL;
   (*fdf)->mlx = NULL;
   (*fdf)->img = NULL;
   (*fdf)->camera = NULL;
   (*fdf)->map = read_map(map_name, *fdf);
}

int main(int ac, char **av)
{

   t_fdf *fdf;

   if ((ac != 2) || (!validate_map(av[1])))
      ft_printf("Invalid map or map doesn't exist");
   init_fdf(&fdf, av[1]);
   kill_everything(fdf);
   return 0;
}
