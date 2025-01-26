#ifndef FDF_H
# define FDF_H

// INCLUDES
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft_plus/includes/ft_ctype.h"
# include "../libs/libft_plus/includes/ft_string_functions.h"
# include "../libs/libft_plus/includes/not_in_standard_includes/ft_printf_bonus.h"
# include "../libs/libft_plus/includes/not_in_standard_includes/get_next_line.h"
# include "../libs/libft_plus/includes/not_in_standard_includes/not_in_standard.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

// MACROS UTILS
# define TRUE 1
# define FALSE 0
# define SCREEN_WIDTH 1300
# define SCREEN_HEIGHT 900
# define BACKGROUND_COLOR 0x00000000
# define DRAWING_COLOR 0x00FFFFFF
# define COS_30 0.86602540378
# define SIN_30 0.5

// STRUCTS UTILS
typedef struct s_references
{
	float			x;
	float			y;
	float			z;
}					t_references;

typedef struct s_map
{
	t_references	*s_references;
	struct s_map	*next;
	int				width;
	int				height;
	float			scale;
}					t_map;

typedef struct s_matrix_width
{
	float			matrix_width;
	float			min_matrix_width;
	float			max_matrix_width;
}					t_matrix_width;

typedef struct s_matrix_height
{
	float			matrix_height;
	float			min_matrix_height;
	float			max_matrix_height;
}					t_matrix_height;

typedef struct s_matrix_dimensions
{
	float			matrix_height;
	float			matrix_width;
}					t_matrix_dimensions;

typedef struct s_data_draw_line
{
	int				dx;
	int				dy;
	int				control;
	int				inc_x;
	int				inc_y;
	mlx_image_t		*img;
}					t_data_draw_line;

typedef struct s_fdf
{
	t_map			*s_map;
	mlx_t			*mlx;
	mlx_image_t		*img;
    int             color;
    int             mouse_x;
    int             mouse_y;
    int             mouse_pressed;
	int 		   	projection;
}				t_fdf;


// FDF INITS
void init_fdf(t_fdf **fdf, char *map_name);
int init_mlx(t_fdf *fdf);
int create_img(t_fdf *fdf);
void set_others(t_fdf *fdf);
int create_map(t_fdf *fdf, char *map_name);

// RUN FDF
void run_fdf(t_fdf **fdf, char *map_name);

// CHECK MAP FILE
int check_map_format(const char *av);
int	print_return(char *message, int return_value);

// READ MAP
t_map	*read_map(char *map_name);

// RENDER
void render(t_fdf *fdf);

// RENDER UTILS
void get_map_scale(t_map *s_map);
t_matrix_dimensions *get_matrix_dimensions(float **map_matrix, t_map *s_map);
float **scale_dimension_matrix(t_map *s_map, float **map_matrix, t_matrix_dimensions *s_matrix_dimensions);

// SETS UTILS
void background(mlx_image_t *img);
t_data_draw_line *new_line_data(mlx_image_t *img, float **converted_matrix, int start, int end);
void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
void scroll_hook(double x_delta, double y_delta, void *param);
void cursor_hook(double xpos, double ypos, void *param);

// UTILS
void free_split(char **split);
void clean_data(t_map *s_map);
void clean_matrix(float **map_matrix);
int	ft_abs(int n);
void put_pixel(mlx_image_t *img, int start, int end, int color);

// DRAW LINE
void draw_line(mlx_image_t *img, float **converted_matrix, int start, int end, int color);

// HANDLE MAP MOVES
void handle_movement_keys(mlx_key_data_t keydata, t_fdf *fdf);
void handle_zoom_keys(mlx_key_data_t keydata, t_fdf *fdf);
void handle_other_keys(mlx_key_data_t keydata, t_fdf *fdf);
void rotate_keys(mlx_key_data_t keydata, t_fdf *fdf);
void rgb_keys(mlx_key_data_t keydata, t_fdf *fdf);

// CAMERA ROTATES
void rotate_x(t_map *map, float angle);
void rotate_y(t_map *map, float angle);
void rotate_z(t_map *map, float angle);

// CAMERA ZOOM 
void zoom_in(t_map *map, float scale);
void zoom_out(t_map *map, float scale);

// CAMERA MOVES
void move_up(t_map *map, float distance);
void move_down(t_map *map, float distance);
void move_left(t_map *map, float distance);
void move_right(t_map *map, float distance);

//PROJECTIONS
void parallel_projection(t_map *s_map, float **map_matrix, int x);
void isometric_projection(t_map *s_map, float **map_matrix, int x);

//DRAW COMMANDS
void draw_comands(mlx_t *mlx);

#endif