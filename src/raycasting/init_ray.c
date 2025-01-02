/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:49:58 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/02 11:35:24 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Cette fonction initialise les variables de base du rayon
// Elle prend en compte la position actuelle du joueur et la largeur de l'écran
//	pour calculer la direction du rayon dans l'espace 3D
// Les calculs utilisent la formule : rayDir = direction + plane * cameraX
// où cameraX est la coordonnée x sur l'écran normalisée entre -1 et 1
void	init_ray_dir(t_ray *ray, t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = data->player.dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = data->player.dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
}

// Cette fonction calcule les distances que le rayon doit parcourir
// 	pour passer d'une ligne de grille à une autre,
// 	horizontalement et verticalement
// Elle utilise la formule de DDA (Digital Differential Analysis)
// pour optimiser les calculs de collision
void	init_ray_dist(t_ray *ray)
{
	if (!ray->ray_dir_x)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (!ray->ray_dir_y)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

// Cette fonction détermine la direction des pas et les distances initiales
// 	pour l'algorithme DDA en fonction de la direction du rayon
// Elle calcule également les distances initiales aux premières intersections
// 	avec les lignes verticales et horizontales de la grille
void	init_ray_step(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}
