/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:56:03 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/13 16:26:53 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_player_pos(t_ray *ray, t_data *data)
{
	ray->pos_x = (double)data->player.pos_x + 0.5;
	ray->pos_y = (double)data->player.pos_y + 0.5;
	set_direction_vectors(ray, data->player.player_dir);
	data->player.dir_x = ray->dir_x;
	data->player.dir_y = ray->dir_y;
	data->player.plane_x = ray->plane_x;
	data->player.plane_y = ray->plane_y;
	data->movement.move_speed = 0.05;
	data->movement.rot_speed = 0.03;
	data->movement.forward = 0;
	data->movement.backward = 0;
	data->movement.left = 0;
	data->movement.right = 0;
	data->movement.rot_left = 0;
	data->movement.rot_right = 0;
}

void	draw_vertical_line(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		data->img.addr[y * WINDOW_WIDTH + x] = data->c_color;
		y++;
	}
	while (y < ray->draw_end)
	{
		data->img.addr[y * WINDOW_WIDTH + x] = get_texture_color(data, ray, y);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		data->img.addr[y * WINDOW_WIDTH + x] = data->f_color;
		y++;
	}
}

void	raycasting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	init_player_pos(&ray, data);
	while (x < WINDOW_WIDTH)
	{
		init_ray_dir(&ray, data, x);
		init_ray_dist(&ray);
		init_ray_step(&ray);
		perform_dda(&ray, data);
		calculate_wall_dist(&ray);
		calculate_line_height(&ray);
		draw_vertical_line(data, &ray, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
