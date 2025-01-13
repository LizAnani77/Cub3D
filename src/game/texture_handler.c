/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:12:58 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/13 16:30:15 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// int	load_texture(t_data *data, t_texture **texture, char *path)
// {
// 	*texture = malloc(sizeof(t_texture));
// 	if (!*texture)
// 		return (1);
// 	(*texture)->img = mlx_xpm_file_to_image(data->mlx, path, &(*texture)->width,
// 			&(*texture)->height);
// 	if (!(*texture)->img)
// 	{
// 		free(*texture);
// 		return (1);
// 	}
// 	(*texture)->addr = mlx_get_data_addr((*texture)->img,
// 			&(*texture)->bits_per_pixel, &(*texture)->line_length,
// 			&(*texture)->endian);
// 	return (0);
// }

int	load_texture(t_data *data, t_texture **texture, char *path)
{
	int	width;
	int	height;

	printf("Attempting to load texture from: %s\n", path);
	if (!path || access(path, F_OK) == -1)
	{
		printf("Error: texture file does not exist: %s\n", path);
		return (1);
	}
	*texture = malloc(sizeof(t_texture));
	if (!*texture)
	{
		printf("Error: malloc failed for texture structure\n");
		return (1);
	}
	(*texture)->img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!(*texture)->img)
	{
		printf("Error: failed to load XPM file: %s\n", path);
		free(*texture);
		return (1);
	}
	(*texture)->width = width;
	(*texture)->height = height;
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	if (!(*texture)->addr)
	{
		printf("Error: failed to get texture data address\n");
		mlx_destroy_image(data->mlx, (*texture)->img);
		free(*texture);
		return (1);
	}
	printf("Successfully loaded texture: %s (%dx%d)\n", path, width, height);
	return (0);
}

int	init_textures(t_data *data)
{
	printf("Initializing textures...\n");
	printf("North texture path: %s\n", data->n_t);
	printf("South texture path: %s\n", data->s_t);
	printf("West texture path: %s\n", data->w_t);
	printf("East texture path: %s\n", data->e_t);
	if (load_texture(data, &data->no_texture, data->n_t) || load_texture(data,
			&data->so_texture, data->s_t) || load_texture(data,
			&data->we_texture, data->w_t) || load_texture(data,
			&data->ea_texture, data->e_t))
	{
		free_textures(data);
		return (1);
	}
	if (!check_texture_size(data->no_texture, data->so_texture)
		|| !check_texture_size(data->no_texture, data->we_texture)
		|| !check_texture_size(data->no_texture, data->ea_texture))
	{
		printf("Error: textures have inconsistent dimensions\n");
		free_textures(data);
		return (1);
	}
	return (0);
}

int	get_tex_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

int	get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (get_tex_x(data->ea_texture, ray));
		return (get_tex_x(data->we_texture, ray));
	}
	if (ray->ray_dir_y > 0)
		return (get_tex_x(data->so_texture, ray));
	return (get_tex_x(data->no_texture, ray));
}

int	get_tex_x(t_texture *texture, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}
