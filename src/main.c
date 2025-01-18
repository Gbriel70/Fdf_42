#include "../includes/fdf.h"

void init_fdf(t_fdf **fdf, char *map_name)
{
   *fdf = (t_fdf *)malloc(sizeof(t_fdf));
   if (!(*fdf))
      handle_error("Malloc failed", STAGE_NONE, NULL);
   (*fdf)->map = map_read(map_name);
   if (!(*fdf)->map || !validate_map_init((*fdf)->map))
      handle_error("Map initialization failed", STAGE_MAP, (*fdf)->map);
}


int main(int ac, char **av)
{

   t_fdf *fdf;

   if ((ac != 2) || (!validate_map(av[1])))
      handle_error("Invalid map or map doesn't exist", STAGE_NONE, NULL);
   init_fdf(&fdf, av[1]);
   return 0;
}
