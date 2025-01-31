/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:46:56 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/08 15:06:32 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	error_mlx(char *message, t_data *data)
{
	free_resources(data);
	error_msg(message);
	exit(1);
}

void	error_malloc(char *message, t_data *data)
{
	free_resources(data);
	error_msg(message);
	exit(1);
}

void	error_texture(char *message, t_data *data)
{
	free_resources(data);
	error_msg(message);
	exit(1);
}

void	error_map(char *message, t_data *data)
{
	free_resources(data);
	error_msg(message);
	exit(1);
}

void	exit_with_error(char *message, t_data *data)
{
	if (message)
		ft_putendl_fd(message, 2);
	free_resources(data);
	exit(1);
}
