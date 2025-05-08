/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_udp_reciever.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:14:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 15:16:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"
#include <pthread.h>

pthread_t	client_udp_reciever(int servfd, t_player *lobby);

static void	*reciever(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	char			buffer[MAXLINE + 1];
	size_t			len;
	int				servfd;

	servfd = *(int *)arg;
	ft_printf(LOG">recieving on socket %d%s\n", servfd, RESET);
	while (!0)
	{
		if (!lbb_is_alive(lobby[HOST]))	// temporary way of clean kill
		{
			ft_printfd(STDERR_FILENO, HOSTLOG"host died%s\n", RESET);
			break ;
		}
		ft_memset(buffer, 0, sizeof(buffer));
		// ft_printf("talk to me...\n");
		len = recv(servfd, buffer, MAXLINE, 0);
		if ( len < 0 ) {
			ft_perror(ERROR"recv failed"RESET);
			break;
		}
		if (buffer[0] == '\0')	// really ugly
		{
			ft_printfd(STDERR_FILENO, RED"empty byte recieved\n"RESET);
			continue ;
		}
		ft_printf(YELLOW"%d bytes: '%s' from Server\n"RESET, len, buffer);
		// if (!cycle_player_msgs(buffer, lobby))
		// {
		// 	ft_perror(ERROR"handler failure"RESET);
		// 	break ;
		// }
		// // chaos
		// ft_printf(BLUE"== = = == == =\n");
		// print_quick_lobby(lobby);
		// ft_printf(RESET);
	}
	close(servfd);
	return (NULL);
}
// if (handle_client_players(buffer, recenv) < 0)
// {
// 	ft_printf(HOSTLOG"A NEW HOST WILL RISE%s\n", RESET);
// 	return (close(recenv->player[0].socket), free(recenv), NULL);
// }

/* Spawns a thread that listen to the server for updates on the players */
pthread_t	client_udp_reciever(int servfd, t_player *lobby)
{
	pthread_t	tid;

	(void)lobby;	// <-- this is sad
	if (pthread_create(&tid, NULL, &reciever, &servfd) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return ((pthread_t)0);
	}
	// pthread_detach(tid);
	return (tid);
}