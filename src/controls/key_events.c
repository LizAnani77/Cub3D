/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:05:11 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/02 11:12:25 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Cette fonction gère l'appui des touches du clavier
// Elle met à jour les flags de mouvement dans la structure t_movement
// Les touches WASD contrôlent le déplacement, les flèches la rotation
int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->movement.forward = 1;
	if (keycode == KEY_S)
		data->movement.backward = 1;
	if (keycode == KEY_A)
		data->movement.left = 1;
	if (keycode == KEY_D)
		data->movement.right = 1;
	if (keycode == KEY_LEFT)
		data->movement.rot_left = 1;
	if (keycode == KEY_RIGHT)
		data->movement.rot_right = 1;
	if (keycode == KEY_ESC)
		exit_game(data);
	return (0);
}

// Cette fonction gère le relâchement des touches
// Elle remet à zéro les flags de mouvement correspondants
// Permet d'avoir un contrôle fluide du personnage
int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->movement.forward = 0;
	if (keycode == KEY_S)
		data->movement.backward = 0;
	if (keycode == KEY_A)
		data->movement.left = 0;
	if (keycode == KEY_D)
		data->movement.right = 0;
	if (keycode == KEY_LEFT)
		data->movement.rot_left = 0;
	if (keycode == KEY_RIGHT)
		data->movement.rot_right = 0;
	return (0);
}
