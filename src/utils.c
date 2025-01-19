#include "../includes/fdf.h"

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i] != NULL)
    {
        free(split[i]);
        i++;
    }
    free(split);
}
