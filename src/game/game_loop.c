/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:09:34 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/02 11:11:43 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Cette fonction est le point d'entrée de la boucle principale du jeu
// Elle gère les mouvements, met à jour l'affichage et maintient le jeu en cours
// Elle est appelée en continu par la MLX
int	game_loop(t_data *data)
{
	handle_forward_movement(data);
	handle_strafe_movement(data);
	handle_rotation(data);
	raycasting(data);
	return (0);
}

// Cette fonction initialise les hooks (callbacks) des événements
// Elle connecte les fonctions de gestion des touches aux événements MLX
// Elle configure également la fermeture propre du jeu
void	init_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win, 17, 0, exit_game, data);
	mlx_loop_hook(data->mlx, game_loop, data);
}

// Cette fonction gère la sortie propre du jeu
// Elle libère toutes les ressources allouées
// Elle est appelée lors de l'appui sur ESC ou la fermeture de la fenêtre
int	exit_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_resources(data);
	exit(0);
	return (0);
}
