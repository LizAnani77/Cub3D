/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils 2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:21:18 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/08 22:50:32 by lizzieanani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	get_max_line_length(char **map)
{
	int	max_len;
	int	curr_len;
	int	i;

	max_len = 0;
	i = 0;
	while (map[i])
	{
		curr_len = ft_strlen(map[i]);
		if (curr_len > max_len)
			max_len = curr_len;
		i++;
	}
	return (max_len);
}

int	check_xpm_extension(char *path)
{
	char	*ext;

	ext = ft_strrchr(path, '.');
	if (!ext || ft_strncmp(ext, ".xpm", 5))
		return (0);
	return (1);
}

// int	check_texture_size(void *texture1, void *texture2)
// {
// 	int	width1;
// 	int	height1;
// 	int	width2;
// 	int	height2;

// 	mlx_get_image_size(texture1, &width1, &height1);
// 	mlx_get_image_size(texture2, &width2, &height2);
// 	return (width1 == width2 && height1 == height2);
// }

int	check_texture_size(t_texture *texture1, t_texture *texture2)
{
	return (texture1->width == texture2->width
		&& texture1->height == texture2->height);
}
