/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:28:13 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/05 22:13:03 by lizzieanani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	free_texture(void *mlx, void *texture, char *path)
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

void	free_textures(t_data *data)
{
	free_texture(data->mlx, data->no_texture, data->n_t);
	free_texture(data->mlx, data->so_texture, data->s_t);
	free_texture(data->mlx, data->we_texture, data->w_t);
	free_texture(data->mlx, data->ea_texture, data->e_t);
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

void	free_resources(t_data *data)
{
	free_map_array(data->map, data->map_height);
	data->map = NULL;
	free_map_array(data->copie_map, data->map_height);
	data->copie_map = NULL;
	free_textures(data);
	free_mlx_resources(data);
}
