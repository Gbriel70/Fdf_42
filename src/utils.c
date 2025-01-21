#include "../includes/fdf.h"

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
}

int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

uint32_t put_alpha(uint32_t color)
{
	uint32_t	alpha;
	unsigned char	*color_ptr;

	alpha = color << 8;
	color_ptr = (unsigned char *)&alpha;
	*color_ptr = 255;
	return (alpha);
}

int	ft_hex_to_int(char *str)
{
	int	result;
	int	byte;

	result = 0;
	while (*str != ' ' && *str)
	{
		byte = *str++;
		if (byte >= '0' && byte <= '9')
			byte -= '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		result = (result << 4) | (byte & 0xF);
	}
	return (result);
}