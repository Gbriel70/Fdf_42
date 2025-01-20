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
# include "../libs/libft_plus/includes/ft_ctype.h"

// MACROS UTILS
# define TRUE 1
# define FALSE 0
# define BACKGROUND_COLOR 0x000000
# define SCREEN_WIDTH 1300
# define SCREEN_HEIGHT 900
# define HEXA_BASE 16

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
void clear_invalid_map(t_fdf *fdf, t_map *map);
void print_error(int stage);
void kill_everything(t_fdf *fdf);

// CHECK UTILS
short   validate_map(char *map_name);

// READ MAP
t_map *read_map(char *map_name, t_fdf *fdf);

// READ MAP UTILS
short   valid_map_width(int fd, int width);
t_references **set_matrix(int width, int height);
void fill_matrix(t_map *map, char **split_line, int height);
void	center_to_origin(t_map *map);

// UTILS
void free_split(char **split);

# endif