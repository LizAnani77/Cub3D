/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:37:46 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/08 11:28:59 by lanani-f         ###   ########.fr       */
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

// int	get_texure_color(t_data *data, t_ray *ray, int y)
// {
// 	int		tex_x;
// 	int		tex_y;
// 	void	*texture;
// 	int		tex_height;
// 	double	step;

// 	texture = select_texture(data, ray);
// 	tex_x = get_tex_x(texture, ray);
// 	mlx_get_image_size(texture, NULL, &tex_height);
// 	step = 1.0 * tex_height / ray->line_height;
// 	tex_y = (int)((y - ray->draw_start) * step);
// 	adjust_tex_y(&tex_y, tex_height);
// 	return (get_tex_color(texture, tex_x, tex_y));
// }
int get_texture_color(t_data *data, t_ray *ray, int y)
{
    int         tex_x;
    int         tex_y;
    t_texture   *texture;
    double      step;

    texture = select_texture(data, ray);
    tex_x = get_tex_x(texture, ray);
    step = 1.0 * texture->height / ray->line_height;
    tex_y = (int)((y - ray->draw_start) * step);
    adjust_tex_y(&tex_y, texture->height);
    return (get_tex_color(texture, tex_x, tex_y));
}


static void	check_texture_paths(t_data *data)
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

int	load_all_textures(t_data *data)
{
	check_texture_paths(data);
	if (!check_xpm_extension(data->n_t) || !check_xpm_extension(data->s_t)
		|| !check_xpm_extension(data->w_t) || !check_xpm_extension(data->e_t))
		return (error_msg("Les textures doivent être au format .xpm"));
	if (load_texture(data, &data->no_texture, data->n_t))
		return (error_msg("Erreur lors du chargement de la texture nord"));
	if (load_texture(data, &data->so_texture, data->s_t))
		return (error_msg("Erreur lors du chargement de la texture sud"));
	if (load_texture(data, &data->we_texture, data->w_t))
		return (error_msg("Erreur lors du chargement de la texture ouest"));
	if (load_texture(data, &data->ea_texture, data->e_t))
		return (error_msg("Erreur lors du chargement de la texture est"));
	if (validate_textures(data))
		return (1);
	return (0);
}

void	*get_wall_texture_ptr(t_data *data, t_ray *ray)
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
