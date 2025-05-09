/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 14:19:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minigame.h"
#include <unistd.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	char		buffer[92];
	pthread_t	tid;
	
	if (mlx->thread)
		tid = *(pthread_t *)mlx->thread;
	// host and players tell the others to kill them the same way
	buffer_player_action(mlx->lobby[*mlx->index], "kill", buffer);
	
	//game_sender
	send_all(mlx, buffer, ft_strlen(buffer), 0);
	// if (*mlx->index == HOST)
	// 	ft_memcpy(&socket, mlx->lobby[HOST].online, sizeof(int));
	// else
	// 	ft_memcpy(&socket, &mlx->lobby[HOST].online, sizeof(int));
	shutdown(*mlx->socket, SHUT_RDWR);
	close(*mlx->socket);	// gets the threads out of the syscall
	// lbb_kill_player(buffer);	// gets the thread out of the loop
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	//print_lobby(mlx->lobby);
	free(mlx->mlx);
	// if (pthread_join(tid, NULL) != 0) { /* throw error */ }
	*mlx->index = -1;
	// ! ! !  ! ! ! ! ! ! ! ! ! ! ! | set index -1 | ! ! ! ! ! ! ! ! ! ! !
	sleep(1);
	// wait the thread
	// lbb_delete_lobby((lbb_get_ptr(NULL)));
	// 
	exit(EXIT_SUCCESS);
	return (0);
}
