/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:12:58 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/13 13:40:10 by lanani-f         ###   ########.fr       */
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



int load_texture(t_data *data, t_texture **texture, char *path)
{
    printf("Attempting to load texture from: %s\n", path);
    
    // Vérification du chemin
    if (!path || access(path, F_OK) == -1)
    {
        printf("Error: texture file does not exist: %s\n", path);
        return (1);
    }
    
    // Allocation de la structure
    *texture = malloc(sizeof(t_texture));
    if (!*texture)
    {
        printf("Error: malloc failed for texture structure\n");
        return (1);
    }
    
    // Chargement de l'image
    int width, height;
    (*texture)->img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
    if (!(*texture)->img)
    {
        printf("Error: failed to load XPM file: %s\n", path);
        free(*texture);
        return (1);
    }
    
    (*texture)->width = width;
    (*texture)->height = height;
    
    // Récupération de l'adresse des données
    (*texture)->addr = mlx_get_data_addr((*texture)->img,
            &(*texture)->bits_per_pixel,
            &(*texture)->line_length,
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

// int load_all_texture(t_data *data)
// {
//     // Vérification préalable des chemins des textures
//     check_texture_paths(data);

//     data->no_texture = malloc(sizeof(t_texture));
//     data->so_texture = malloc(sizeof(t_texture));
//     data->we_texture = malloc(sizeof(t_texture));
//     data->ea_texture = malloc(sizeof(t_texture));

//     if (!data->no_texture || !data->so_texture || 
//         !data->we_texture || !data->ea_texture)
//     {
//         free_textures(data);
//         return (error_msg("Erreur d'allocation mémoire pour les textures"));
//     }
//     printf("Loading North texture...\n");
//     data->no_texture->img = mlx_xpm_file_to_image(data->mlx, data->n_t,
//         &data->no_texture->width, &data->no_texture->height);
//     printf("Loading South texture...\n");
//     data->so_texture->img = mlx_xpm_file_to_image(data->mlx, data->s_t,
//         &data->so_texture->width, &data->so_texture->height);
//     printf("Loading West texture...\n");
//     data->we_texture->img = mlx_xpm_file_to_image(data->mlx, data->w_t,
//         &data->we_texture->width, &data->we_texture->height);
//     printf("Loading East texture...\n");
//     data->ea_texture->img = mlx_xpm_file_to_image(data->mlx, data->e_t,
//         &data->ea_texture->width, &data->ea_texture->height);

//     if (!data->no_texture->img || !data->so_texture->img || 
//         !data->we_texture->img || !data->ea_texture->img)
//     {
//         free_textures(data);
//         return (error_msg("Erreur lors du chargement des textures"));
//     }
//     data->no_texture->addr = mlx_get_data_addr(data->no_texture->img,
//         &data->no_texture->bits_per_pixel, &data->no_texture->line_length,
//         &data->no_texture->endian);
//     data->so_texture->addr = mlx_get_data_addr(data->so_texture->img,
//         &data->so_texture->bits_per_pixel, &data->so_texture->line_length,
//         &data->so_texture->endian);
//     data->we_texture->addr = mlx_get_data_addr(data->we_texture->img,
//         &data->we_texture->bits_per_pixel, &data->we_texture->line_length,
//         &data->we_texture->endian);
//     data->ea_texture->addr = mlx_get_data_addr(data->ea_texture->img,
//         &data->ea_texture->bits_per_pixel, &data->ea_texture->line_length,
//         &data->ea_texture->endian);

//     if (!data->no_texture->addr || !data->so_texture->addr || 
//         !data->we_texture->addr || !data->ea_texture->addr)
//     {
//         free_textures(data);
//         return (error_msg("Erreur lors de la récupération des adresses des textures"));
//     }
//     return (0);
// }


// int	init_textures(t_data *data)
// {
// 	if (load_texture(data, &data->no_texture, data->n_t))
// 		return (1);
// 	if (load_texture(data, &data->so_texture, data->s_t))
// 		return (1);
// 	if (load_texture(data, &data->we_texture, data->w_t))
// 		return (1);
// 	if (load_texture(data, &data->ea_texture, data->e_t))
// 		return (1);
// 	return (0);
// }


// int init_textures(t_data *data)
// {
//     if (!data || !data->mlx)
//         return (error_msg("MLX context is not initialized"));

//     // Vérifie d'abord que tous les chemins de texture sont valides
//     if (!check_xpm_extension(data->n_t) || !check_xpm_extension(data->s_t)
//         || !check_xpm_extension(data->w_t) || !check_xpm_extension(data->e_t))
//         return (error_msg("Les textures doivent être au format .xpm"));

//     // Charge toutes les textures
//     if (load_all_texture(data))
//     {
//         free_textures(data);
//         return (error_msg("Erreur lors du chargement des textures"));
//     }

//     // Vérifie que les dimensions des textures sont cohérentes
//     if (!check_texture_size(data->no_texture, data->so_texture)
//         || !check_texture_size(data->no_texture, data->we_texture)
//         || !check_texture_size(data->no_texture, data->ea_texture))
//     {
//         free_textures(data);
//         return (error_msg("Les textures doivent avoir la même taille"));
//     }

//     return (0);
// }


int init_textures(t_data *data)
{
    printf("Initializing textures...\n");
    printf("North texture path: %s\n", data->n_t);
    printf("South texture path: %s\n", data->s_t);
    printf("West texture path: %s\n", data->w_t);
    printf("East texture path: %s\n", data->e_t);

    if (load_texture(data, &data->no_texture, data->n_t) ||
        load_texture(data, &data->so_texture, data->s_t) ||
        load_texture(data, &data->we_texture, data->w_t) ||
        load_texture(data, &data->ea_texture, data->e_t))
    {
        free_textures(data);
        return (1);
    }

    // Vérification des dimensions
    if (!check_texture_size(data->no_texture, data->so_texture) ||
        !check_texture_size(data->no_texture, data->we_texture) ||
        !check_texture_size(data->no_texture, data->ea_texture))
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
