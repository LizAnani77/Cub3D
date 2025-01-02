/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:18:45 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/02 11:46:52 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Ces fonctions configurent les vecteurs de direction et le plan de la caméra
// selon l'orientation initiale du joueur (N, S, E, W)
// dir_x et dir_y forment le vecteur de direction du joueur
// plane_x et plane_y forment le plan de la caméra perpendiculaire
//	à la direction
// Ces valeurs sont utilisées pour le calcul du raycasting
static void	set_direction_ns(t_ray *ray, char dir)
{
	if (dir == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	if (dir == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
}

static void	set_direction_ew(t_ray *ray, char dir)
{
	if (dir == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	if (dir == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

void	set_direction_vectors(t_ray *ray, char dir)
{
	set_direction_ns(ray, dir);
	set_direction_ew(ray, dir);
}
