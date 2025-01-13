/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:47:43 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/13 16:25:43 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_texture_paths(t_data *data)
{
	if (data->n_t)
		free(data->n_t);
	if (data->s_t)
		free(data->s_t);
	if (data->w_t)
		free(data->w_t);
	if (data->e_t)
		free(data->e_t);
	data->n_t = NULL;
	data->s_t = NULL;
	data->w_t = NULL;
	data->e_t = NULL;
}

// void	free_textures(t_data *data)
// {
// 	if (data->no_texture)
// 		mlx_destroy_image(data->mlx, data->no_texture);
// 	if (data->so_texture)
// 		mlx_destroy_image(data->mlx, data->so_texture);
// 	if (data->we_texture)
// 		mlx_destroy_image(data->mlx, data->we_texture);
// 	if (data->ea_texture)
// 		mlx_destroy_image(data->mlx, data->ea_texture);
// 	data->no_texture = NULL;
// 	data->so_texture = NULL;
// 	data->we_texture = NULL;
// 	data->ea_texture = NULL;
// }

void	free_textures(t_data *data)
{
	if (data->no_texture)
	{
		if (data->no_texture->img)
			mlx_destroy_image(data->mlx, data->no_texture->img);
		free(data->no_texture);
		data->no_texture = NULL;
	}
	if (data->so_texture)
	{
		if (data->so_texture->img)
			mlx_destroy_image(data->mlx, data->so_texture->img);
		free(data->so_texture);
		data->so_texture = NULL;
	}
	if (data->we_texture)
	{
		if (data->we_texture->img)
			mlx_destroy_image(data->mlx, data->we_texture->img);
		free(data->we_texture);
		data->we_texture = NULL;
	}
	if (data->ea_texture)
	{
		if (data->ea_texture->img)
			mlx_destroy_image(data->mlx, data->ea_texture->img);
		free(data->ea_texture);
		data->ea_texture = NULL;
	}
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (i < data->map_height)
		{
			if (data->map[i])
				free(data->map[i]);
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
}

void	free_mlx(t_data *data)
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
	data->img.img = NULL;
	data->win = NULL;
	data->mlx = NULL;
}

// free_texture a ajouter?
void	free_resources(t_data *data)
{
	free_texture_paths(data);
	free_textures(data);
	free_map(data);
	free_mlx(data);
}
