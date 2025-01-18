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

t_references **alloc_matrix(int height, int width)
{
    t_references **matrix;
    int i;

    matrix = (t_references **)malloc(sizeof(t_references *) * height);
    if (!matrix)
        return (NULL);
    i = 0;
    while (i < height)
    {
        matrix[i] = (t_references *)malloc(sizeof(t_references) * width);
        if (!matrix[i])
        {
            while (i > 0)
                free(matrix[--i]);
            free(matrix);
            return (NULL);
        }
        i++;
    }
    return (matrix);
}

int check_lines(int fd, int size)
{
    int     check;
    int     word_count;
    char    *line;
    char    **div_line;

    check = 1;
    word_count = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break;
        div_line = ft_split(line, ' ');
        while (div_line[word_count] != NULL && div_line[word_count][0] != '\n')
            word_count++;
        if (word_count != size)
            check = 0;
        word_count = 0;
        free(line);
        ft_free_array(div_line);
    }
    get_next_line(-1);
    return check;
}

int	ft_hex_to_int(char *hexa)
{
	int	res;
	int	byte;

	res = 0;
	while (*hexa != ' ' && *hexa)
	{
		byte = *hexa++;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		res = (res << 4) | (byte & 0xF);
	}
	return (res);
}
