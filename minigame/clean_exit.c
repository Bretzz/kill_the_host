/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 21:47:47 by totommi          ###   ########.fr       */
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
	if (mlx->thread)
		tid = *(pthread_t *)mlx->thread;

	// tell the others to kill them
	buffer_player_action(mlx->lobby[*mlx->index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer), 0);

	// shutting down the 'online' thread
	*mlx->index = -1; // gets the thread out of the loop
	// usleep(100);
	shutdown(*mlx->socket, SHUT_RDWR);
	close(*mlx->socket);	// gets the threads out of the syscall
	
	//freeing mlx resources 
	mlx_destroy_window(mlx->mlx, mlx->win);
	// mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	// *mlx->index = -1;
	// ! ! !  ! ! ! ! ! ! ! ! ! ! ! | set index -1 | ! ! ! ! ! ! ! ! ! ! !
	// wait the thread
	if (tid && pthread_join(tid, NULL) != 0) { /* throw error */ }
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	free_mtx((void **)mlx->map);
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
