/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:56:27 by ale               #+#    #+#             */
/*   Updated: 2025/02/27 18:39:57 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = -1;
	if (map)
	{
		while (map[++i])
			free(map[i]);
		free(map);
	}
}

int	close_game(t_mlx_data *data)
{
	int	i;

	i = -1;
	if (data->map)
	{
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
	cleanup_map_and_textures(data);
	clean_init_and_window(data);
	exit(0);
}

void	cleanup_map_and_textures(t_mlx_data *data)
{
	if (data->floor)
		mlx_destroy_image(data->mlx, data->floor);
	if (data->player)
		mlx_destroy_image(data->mlx, data->player);
	if (data->wall)
		mlx_destroy_image(data->mlx, data->wall);
	if (data->exit)
		mlx_destroy_image(data->mlx, data->exit);
	if (data->ice_cr)
		mlx_destroy_image(data->mlx, data->ice_cr);
}

void	clean_init_and_window(t_mlx_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
}
