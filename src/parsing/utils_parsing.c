/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:03:08 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/06 17:08:55 by lizzieanani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Vérifie l'extension du fichier .cub
int	check_file_extension(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".cub", 5))
		return (0);
	return (1);
}

// Vérifie si la ligne contient uniquement des espaces ou des tabs
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// Parse les couleurs RGB (F et C)
int	parse_color(char *str)
{
	char	**split;
	int		rgb[3];
	int		i;
	int		result;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (-1);
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_split(split);
			return (-1);
		}
		i++;
	}
	result = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_split(split);
	return (result);
}

// Vérifie si le caractère est valide pour la map
int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

// Vérifie si le caractère est une position de départ valide
int	is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
