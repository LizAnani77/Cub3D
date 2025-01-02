/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:28:13 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/02 11:52:44 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Fonction de nettoyage textures
void	free_textures(t_data *data)
{
	if (data->no_texture)
	{
		mlx_destroy_image(data->mlx, data->no_texture);
		free(data->n_t);
	}
	if (data->so_texture)
	{
		mlx_destroy_image(data->mlx, data->so_texture);
		free(data->s_t);
	}
	if (data->we_texture)
	{
		mlx_destroy_image(data->mlx, data->we_texture);
		free(data->w_t);
	}
	if (data->ea_texture)
	{
		mlx_destroy_image(data->mlx, data->ea_texture);
		free(data->e_t);
	}
}

// Fonction de nettoyage ressources
void	free_map_array(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

void	free_mlx_resources(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	free_resources(t_data *data)
{
	free_map_array(data->map, data->map_height);
	free_map_array(data->copie_map, data->map_height);
	free_textures(data);
	free_mlx_resources(data);
}
