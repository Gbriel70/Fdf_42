#include "../includes/fdf.h"

void	ft_free_array(char **array)
{
    int	i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

int	**alloc_matrix(int height, int width)
{
    int	**matrix;
    int	i;

    matrix = malloc(sizeof(int *) * height);
    if (!matrix)
        return (NULL);
    i = 0;
    while (i < height)
    {
        matrix[i] = malloc(sizeof(int) * width);
        if (!matrix[i])
        {
            while (--i >= 0)
                free(matrix[i]);
            free(matrix);
            return (NULL);
        }
        i++;
    }
    return (matrix);
}
