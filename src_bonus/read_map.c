/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:22:40 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/01/24 09:26:29 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

int parse_color(char *token)
{
	char *comma;

	comma = ft_strchr(token, ',');
	if (comma)
		return (ft_atoi_base(comma + 1, 16));
	return (0xFF00FF);
}

int parse_height(char *token)
{
	char *comma;
	int height;

	comma = ft_strchr(token, ',');
	if(comma)
		*comma = '\0';
	height = ft_atoi(token);
	if (comma)
		*comma = ',';
	return (height);
}

static t_map	*insert_node(t_map *head, t_map *s_list)
{
	t_map	*current;

	current = head;
	if (!s_list)
		return (head);
	if (!head)
	{
		head = s_list;
		current = head;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = s_list;
		current = current->next;
	}
	return (head);
}

static t_map	*new_node(int x, int y, int z, int color)
{
	t_map	*new;

	new = (t_map *)malloc(sizeof(t_map));
	if (!new)
		print_return("In function new_node Malloc failed", 0);
	new->s_references = (t_references *)malloc(sizeof(t_references));
	if (!new->s_references)
		free(new);
	new->s_references->x = x;
	new->s_references->y = y;
	new->s_references->z = z;
	new->s_references->color = color;
	new->next = NULL;
	return (new);
}

static t_map	*new_list(char *line, int y)
{
	int		x;
	int		z;
	int 	color;
	char	**split_result;
	t_map	*s_list;

	x = -1;
	s_list = NULL;
	split_result = ft_split(line, ' ');
	if (!split_result)
		free_split(split_result);
	while (split_result[++x])
	{
		color = parse_color(split_result[x]);
		z = parse_height(split_result[x]);
		s_list = insert_node(s_list, new_node(x, y, z, color));
	}
	s_list->width = x;
	free_split(split_result);
	return (s_list);
}

t_map	*read_map(char *map_name)
{
	t_map	*temp_map;
	char	*line;
	int		fd;
	int		y;

	fd = open(map_name, O_RDONLY);
	y = 0;
	temp_map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp_map = insert_node(temp_map, new_list(line, y));
		y++;
		free(line);
	}
	if (!temp_map || temp_map->width < 2)
	{
		clean_data(temp_map);
		return (NULL);
	}
	temp_map->height = y;
	close(fd);
	return (temp_map);
}
