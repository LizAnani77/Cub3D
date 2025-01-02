/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:08:20 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/02 11:12:12 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Cette fonction gère la rotation de la caméra
// Elle utilise une matrice de rotation 2D pour faire pivoter
// à la fois le vecteur de direction et le plan de la caméra
// La rotation est appliquée en fonction de la vitesse de rotation
void	handle_rotation(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->movement.rot_right)
	{
		old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-data->movement.rot_speed)
			- data->player.dir_y * sin(-data->movement.rot_speed);
		data->player.dir_y = old_dir_x * sin(-data->movement.rot_speed)
			+ data->player.dir_y * cos(-data->movement.rot_speed);
		old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x
			* cos(-data->movement.rot_speed) - data->player.plane_y
			* sin(-data->movement.rot_speed);
		data->player.plane_y = old_plane_x * sin(-data->movement.rot_speed)
			+ data->player.plane_y * cos(-data->movement.rot_speed);
	}
	handle_rotation_left(data);
}

// Cette fonction gère spécifiquement la rotation vers la gauche
// Séparée pour respecter la limite de 25 lignes par fonction
// Utilise les mêmes calculs que la rotation droite mais avec un angle opposé
void	handle_rotation_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->movement.rot_left)
	{
		old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(data->movement.rot_speed)
			- data->player.dir_y * sin(data->movement.rot_speed);
		data->player.dir_y = old_dir_x * sin(data->movement.rot_speed)
			+ data->player.dir_y * cos(data->movement.rot_speed);
		old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x
			* cos(data->movement.rot_speed) - data->player.plane_y
			* sin(data->movement.rot_speed);
		data->player.plane_y = old_plane_x * sin(data->movement.rot_speed)
			+ data->player.plane_y * cos(data->movement.rot_speed);
	}
}
