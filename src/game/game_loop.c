/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:09:34 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/05 14:16:05 by lizzieanani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	game_loop(t_data *data)
{
	handle_forward_movement(data);
	handle_strafe_movement(data);
	handle_rotation(data);
	raycasting(data);
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win, 17, 0, exit_game, data);
	mlx_loop_hook(data->mlx, game_loop, data);
}

int	exit_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_resources(data);
	exit(0);
	return (0);
}
