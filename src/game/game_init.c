/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:14:08 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/10 15:19:37 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_with_error("MLX initialization failed", data);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!data->win)
		exit_with_error("Window creation failed", data);
}

void	init_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img.img)
		exit_with_error("Image creation failed", data);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
}

// int	init_game(t_data *data)
// {
// 	init_window(data);
// 	init_image(data);
// 	if (init_textures(data))
// 		return (1);
// 	init_hooks(data);
// 	return (0);
// }

int init_game(t_data *data)
{
    printf("Starting game initialization...\n");
    init_window(data);
    printf("Window initialized...\n");
    init_image(data);
    printf("Image initialized...\n");
    if (init_textures(data))
        return (1);
    printf("Textures initialized...\n");
    init_hooks(data);
    printf("Hooks initialized...\n");
    return (0);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		data->img.addr[y * WINDOW_WIDTH + x] = color;
}
