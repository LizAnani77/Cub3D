/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:56:03 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/02 11:21:21 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Cette fonction initialise toutes les valeurs nécessaires au démarrage du jeu
// Elle place le joueur à sa position initiale avec un décalage
//	de 0.5 pour centrer
// Configure la direction initiale selon l'orientation du joueur
// Définit les vitesses de mouvement et de rotation
// Réinitialise tous les flags de mouvement à zéro
void	init_player_pos(t_ray *ray, t_data *data)
{
	ray->pos_x = (double)data->player.pos_x + 0.5;
	ray->pos_y = (double)data->player.pos_y + 0.5;
	set_direction_vectors(ray, data->player.player_dir);
	data->movement.move_speed = 0.05;
	data->movement.rot_speed = 0.03;
	data->movement.forward = 0;
	data->movement.backward = 0;
	data->movement.left = 0;
	data->movement.right = 0;
	data->movement.rot_left = 0;
	data->movement.rot_right = 0;
}

// Cette fonction gère le rendu d'une colonne verticale de l'écran
// Elle dessine le ciel, le mur et le sol pour chaque colonne
// Les couleurs sont définies selon les textures et les paramètres
//	du fichier.cub
void	draw_vertical_line(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		data->img.addr[y * WINDOW_WIDTH + x] = data->c_color;
		y++;
	}
	while (y < ray->draw_end)
	{
		data->img.addr[y * WINDOW_WIDTH + x] = get_texture_color(data, ray, y);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		data->img.addr[y * WINDOW_WIDTH + x] = data->f_color;
		y++;
	}
}

// Cette fonction est la fonction principale du raycasting
// Elle parcourt chaque colonne de l'écran de gauche à droite
// Pour chaque colonne, elle initialise un rayon, calcule les intersections
// 	et dessine la colonne correspondante
void	raycasting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	init_player_pos(&ray, data);
	while (x < WINDOW_WIDTH)
	{
		init_ray_dir(&ray, data, x);
		init_ray_dist(&ray);
		init_ray_step(&ray);
		perform_dda(&ray, data);
		calculate_wall_dist(&ray);
		calculate_line_height(&ray);
		draw_vertical_line(data, &ray, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
