/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 12:28:34 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minigame.h"
#include <unistd.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	char		buffer[92];
	pthread_t	tid;

	tid = 0;
	if (mlx->thread) {tid = *(pthread_t *)mlx->thread;}

	// tell the others to kill them
	buffer_player_action(mlx->lobby[*mlx->index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer), 0);

	// clear resources
	hpc_free(mlx->socket, mlx->index, mlx->thread);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_mtx((void **)mlx->map);
	free(mlx->mlx);

	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
