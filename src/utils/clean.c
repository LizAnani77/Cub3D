/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:28:13 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/09 14:39:06 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	free_texture_bis(void *mlx, void *texture, char *path)
{
	if (texture)
	{
		mlx_destroy_image(mlx, texture);
		texture = NULL;
	}
	if (path)
	{
		free(path);
		path = NULL;
	}
}

void	free_textures_bis(t_data *data)
{
	free_texture_bis(data->mlx, data->no_texture, data->n_t);
	free_texture_bis(data->mlx, data->so_texture, data->s_t);
	free_texture_bis(data->mlx, data->we_texture, data->w_t);
	free_texture_bis(data->mlx, data->ea_texture, data->e_t);
}

void	free_map_array(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
	free(map);
	map = NULL;
}

void	free_mlx_resources(t_data *data)
{
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		data->img.img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	free_texture(t_data *data, t_texture **texture)
{
	if (*texture)
	{
		if ((*texture)->img)
			mlx_destroy_image(data->mlx, (*texture)->img);
		free(*texture);
		*texture = NULL;
	}
}
