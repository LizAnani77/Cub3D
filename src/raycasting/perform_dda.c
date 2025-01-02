/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:51:36 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/02 11:10:31 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Cette fonction implémente l'algorithme DDA (Digital Differential Analysis)
// Elle avance le rayon pas à pas dans la grille jusqu'à ce qu'un mur
//	soit touché
// La variable side indique si le mur touché est vertical (0) ou horizontal (1)
// L'algorithme s'arrête dès qu'un mur (valeur 1 dans la map) est rencontré
void	perform_dda(t_ray *ray, t_data *data)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

// Cette fonction calcule la distance perpendiculaire entre le joueur 
// 	et le mur touché
// La distance perpendiculaire est utilisée pour éviter l'effet fisheye
// Elle prend en compte si le mur touché est vertical ou horizontal 
//	via la variable side
void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

// Cette fonction calcule la hauteur de la ligne à dessiner
// 	ainsi que ses points de début et de fin sur l'écran
// Elle prend en compte la hauteur de l'écran et la distance au mur
// 	pour créer l'effet de profondeur
void	calculate_line_height(t_ray *ray)
{
	ray->line_height = (int)(WINDOW_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}
