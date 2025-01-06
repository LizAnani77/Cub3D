/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:21:18 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/06 18:36:34 by lizzieanani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	count_map_lines(int fd)
{
	char	*line;
	int		count;

	count = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

static char	**allocate_map(int height)
{
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	map[height] = NULL;
	return (map);
}

static int	copy_line_to_map(char **map, char *line, int index)
{
	map[index] = ft_strdup(line);
	if (!map[index])
	{
		free_map_array(map, index);
		return (0);
	}
	return (1);
}

int	init_map(t_data *data, int fd, char *first_line)
{
	int		height;
	char	*line;

	height = count_map_lines(fd);
	data->map = allocate_map(height);
	if (!data->map)
		return (error_msg("Erreur d'allocation de la map"));
	if (!copy_line_to_map(data->map, first_line, 0))
		return (error_msg("Erreur de copie de ligne"));
	data->map_height = height;
	line = get_next_line(fd);
	data->map_height = 1;
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (!copy_line_to_map(data->map, line, data->map_height))
				return (error_msg("Erreur de copie de ligne"));
			data->map_height++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_map(int fd, char *first_line, t_data *data)
{
	if (init_map(data, fd, first_line))
		return (1);
	data->map_width = get_max_line_length(data->map);
	data->copie_map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->copie_map)
		return (error_msg("Erreur d'allocation de la copie de la map"));
	data->copie_map[data->map_height] = NULL;
	return (0);
}
