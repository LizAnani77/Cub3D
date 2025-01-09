/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:12:58 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/09 11:39:28 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// int	load_texture(t_data *data, void **texture, char *path)
// {
// 	int	width;
// 	int	height;

// 	*texture = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
// 	if (!*texture)
// 		return (error_msg("Failed to load texture"));
// 	return (0);
// }

int load_texture(t_data *data, t_texture **texture, char *path)
{
    *texture = malloc(sizeof(t_texture));
    if (!*texture)
        return (1);
    
    (*texture)->img = mlx_xpm_file_to_image(data->mlx, path, 
                                           &(*texture)->width, 
                                           &(*texture)->height);
    if (!(*texture)->img)
    {
        free(*texture);
        return (1);
    }
    (*texture)->addr = mlx_get_data_addr((*texture)->img, 
                                        &(*texture)->bits_per_pixel,
                                        &(*texture)->line_length,
                                        &(*texture)->endian);
    return (0);
}

int init_textures(t_data *data)
{
	if (load_texture(data, &data->no_texture, data->n_t))
		return (1);
	if (load_texture(data, &data->so_texture, data->s_t))
		return (1);
	if (load_texture(data, &data->we_texture, data->w_t))
		return (1);
	if (load_texture(data, &data->ea_texture, data->e_t))
		return (1);
	return (0);
}

int	get_tex_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (tex_y * texture->line_length
			+ tex_x * (texture->bits_per_pixel / 8));
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

// int	get_tex_x(void *texture, t_ray *ray)
// {
// 	double	wall_x;
// 	int		tex_x;
// 	int		tex_width;
// 	int		tex_height;

// 	mlx_get_image_size(texture, &tex_width, &tex_height);
// 	if (ray->side == 0)
// 		wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
// 	else
// 		wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * tex_width);
// 	if ((ray->side == 0 && ray->ray_dir_x > 0)
// 		|| (ray->side == 1 && ray->ray_dir_y < 0))
// 		tex_x = tex_width - tex_x - 1;
// 	return (tex_x);
// }

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
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}
