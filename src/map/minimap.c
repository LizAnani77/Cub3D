/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:00:00 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/08 15:03:10 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_minimap(t_data *data)
{
	int	max_dim;

	max_dim = data->map_width;
	if (data->map_height > max_dim)
		max_dim = data->map_height;
	data->minimap.scale = MINIMAP_SIZE / max_dim;
	if (data->minimap.scale < 2)
		data->minimap.scale = 2;
	data->minimap.width = data->map_width * data->minimap.scale;
	data->minimap.height = data->map_height * data->minimap.scale;
	data->minimap.offset_x = 10;
	data->minimap.offset_y = 10;
}

void	put_pixel_minimap(t_data *data, int x, int y, int color)
{
	if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH)
		data->img.addr[y * WINDOW_WIDTH + x] = color;
}

void	put_minimap_pixel(t_data *data, int map_x, int map_y, int color)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	i = 0;
	while (i < data->minimap.scale)
	{
		j = 0;
		while (j < data->minimap.scale)
		{
			screen_x = data->minimap.offset_x + (map_x * data->minimap.scale
					+ i);
			screen_y = data->minimap.offset_y + (map_y * data->minimap.scale
					+ j);
			put_pixel_minimap(data, screen_x, screen_y, color);
			j++;
		}
		i++;
	}
}

void	draw_map_content(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				put_minimap_pixel(data, x, y, 0x808080);
			else if (data->map[y][x] == '0' || ft_strchr("NSEW",
					data->map[y][x]))
				put_minimap_pixel(data, x, y, 0x303030);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data)
{
	if (!data || !data->map)
		return ;
	init_minimap(data);
	draw_map_content(data);
	draw_player_on_map(data);
}
