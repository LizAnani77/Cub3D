/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:42:52 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/08 14:34:03 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (error_msg("Usage: ./cub3D <map.cub>"));
	ft_memset(&data, 0, sizeof(t_data));
	if (parse_file(av[1], &data))
	{
		free_resources(&data);
		return (1);
	}
	if (init_game(&data))
	{
		free_resources(&data);
		return (1);
	}
	mlx_loop(data.mlx);
	free_resources(&data);
	return (0);
}
