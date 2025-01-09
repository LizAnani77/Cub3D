/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:42:17 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/09 14:47:27 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
