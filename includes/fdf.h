#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft_plus/includes/not_in_standard_includes/ft_printf_bonus.h"
# include "../libs/libft_plus/includes/not_in_standard_includes/get_next_line.h"
# include "../libs/libft_plus/includes/ft_string_functions.h"
# include "../libs/libft_plus/includes/not_in_standard_includes/not_in_standard.h"

// MACROS UTILS
# define TRUE 1
# define FALSE 0
# define BACKGROUND_COLOR 0x000000
# define SCREEN_WIDTH 1300
# define SCREEN_HEIGHT 900
# define STAGE_NONE 0
# define STAGE_MAP 1
# define STAGE_MATRIX 2
# define STAGE_MLX 3
# define STAGE_FULL 4

// STRUCTS UTILS
typedef struct s_references
{
    float       x;
    float       y;
    float       z;
    uint32_t    color;
}               t_references;

typedef struct s_map
{
    int             width;
    int             height;
    float           z_scale;
    t_references    **matrix;
}               t_map;

typedef struct s_draw_line
{
    int     d_x;
    int     d_y;
    int     control;
    int     inc_x;
    int     inc_y;
}               t_draw_line;

typedef struct s_camera
{
    float       x;
    float       y;
    float       z;
    float       scale;
}               t_camera;

typedef struct s_fdf
{
    t_map           *map;
    t_camera        *camera;
    mlx_t           *mlx;
    mlx_image_t     *img;
}                   t_fdf;

// ERROS UTILS
void handle_error(char *error_message, int stage, void *ptr);
void cleanup_resources(t_fdf *fdf);

// READ MAP
t_map *map_read(char *map_name);

// READ MAP UTILS
void convert_map(t_map *map, char *n_map);
void center_map(t_map *map);

// CHECK UTILS
short   validate_map(char *map_name);
short	validate_map_init(t_map *map);

// UTILS
void ft_free_array(char **array);
t_references **alloc_matrix(int height, int width);
int check_lines(int fd, int size);
int	ft_hex_to_int(char *hexa);


# endif