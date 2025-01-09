/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:37:46 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/09 15:06:45 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	validate_textures(t_data *data)
{
	if (!check_xpm_extension(data->n_t) || !check_xpm_extension(data->s_t)
		|| !check_xpm_extension(data->w_t) || !check_xpm_extension(data->e_t))
		return (error_msg("Les textures doivent être au format .xpm"));
	if (!check_texture_size(data->no_texture, data->so_texture)
		|| !check_texture_size(data->no_texture, data->we_texture)
		|| !check_texture_size(data->no_texture, data->ea_texture))
		return (error_msg("Les textures doivent avoir la même taille"));
	return (0);
}

static void	adjust_tex_y(int *tex_y, int tex_height)
{
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= tex_height)
		*tex_y = tex_height - 1;
}

static void	*select_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (data->ea_texture);
		return (data->we_texture);
	}
	if (ray->ray_dir_y > 0)
		return (data->so_texture);
	return (data->no_texture);
}

int	get_texture_color(t_data *data, t_ray *ray, int y)
{
	int			tex_x;
	int			tex_y;
	t_texture	*texture;
	double		step;

	texture = select_texture(data, ray);
	tex_x = get_tex_x(texture, ray);
	step = 1.0 * texture->height / ray->line_height;
	tex_y = (int)((y - ray->draw_start) * step);
	adjust_tex_y(&tex_y, texture->height);
	return (get_tex_color(texture, tex_x, tex_y));
}

void	check_texture_paths(t_data *data)
{
	int	fd;

	fd = open(data->n_t, O_RDONLY);
	if (fd < 0)
		exit_with_error("Impossible d'ouvrir la texture nord", data);
	close(fd);
	fd = open(data->s_t, O_RDONLY);
	if (fd < 0)
		exit_with_error("Impossible d'ouvrir la texture sud", data);
	close(fd);
	fd = open(data->w_t, O_RDONLY);
	if (fd < 0)
		exit_with_error("Impossible d'ouvrir la texture ouest", data);
	close(fd);
	fd = open(data->e_t, O_RDONLY);
	if (fd < 0)
		exit_with_error("Impossible d'ouvrir la texture est", data);
	close(fd);
}
