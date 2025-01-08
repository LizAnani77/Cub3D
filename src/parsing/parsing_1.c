/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:04:59 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/08 11:37:04 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Initialise la structure de données
void	init_data(t_data *data)
{
	data->n_t = NULL;
	data->s_t = NULL;
	data->w_t = NULL;
	data->e_t = NULL;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->f_color = -1;
	data->c_color = -1;
	data->player.pos_x = -1;
	data->player.pos_y = -1;
	data->player.player_dir = '\0';
}

// Parse les textures (NO, SO, WE, EA)
int	parse_texture(char *line, char **texture_path)
{
	char	*trimmed;

	if (*texture_path)
		return (error_msg("Texture déjà définie"));
	trimmed = ft_strtrim(line + 2, " \t\n");
	if (!trimmed)
		return (error_msg("Erreur d'allocation mémoire"));
	*texture_path = ft_strdup(trimmed);
	free(trimmed);
	if (!*texture_path)
		return (error_msg("Erreur d'allocation mémoire"));
	return (0);
}

// Parse une ligne d'identifiant
int	parse_color_identifier(char *line, int *color, char type)
{
	if (*color != -1)
	{
		if (type == 'F')
			return (error_msg("Couleur du sol déjà définie"));
		return (error_msg("Couleur du plafond déjà définie"));
	}
	*color = parse_color(line + 2);
	if (*color == -1)
		return (error_msg("Format de couleur invalide"));
	return (0);
}

int	parse_identifier(char *line, t_data *data)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_texture(line, &data->n_t));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_texture(line, &data->s_t));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_texture(line, &data->w_t));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_texture(line, &data->e_t));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_color_identifier(line, &data->f_color, 'F'));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_color_identifier(line, &data->c_color, 'C'));
	return (error_msg("Identifiant invalide"));
}
