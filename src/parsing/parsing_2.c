/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:02:34 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/09 14:27:24 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_required_elements(t_data *data)
{
	return (data->n_t && data->s_t && data->w_t && data->e_t
		&& data->f_color != -1 && data->c_color != -1);
}

int	process_valid_line(char *line, t_data *data, int fd)
{
	if (!check_required_elements(data))
	{
		if (parse_identifier(line, data))
		{
			free(line);
			return (1);
		}
	}
	else if (parse_map(fd, line, data))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	parse_file_content(int fd, t_data *data)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			ret = process_valid_line(line, data, fd);
			if (ret)
				return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_file(char *filename, t_data *data)
{
	int	fd;

	if (!check_file_extension(filename))
		return (error_msg("Extension de fichier invalide"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Impossible d'ouvrir le fichier"));
	init_data(data);
	if (parse_file_content(fd, data))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (validate_map(data));
}
