/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_reciever.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:33:11 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 02:43:00 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"
#include <pthread.h>

int	client_reciever(int servfd, t_player *lobby);

static void	*reciever(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	char			buffer[MAXLINE];
	size_t			len;
	int				servfd;

	servfd = *(int *)arg;
	while (!0)
	{
		ft_memset(buffer, 0, MAXLINE);
		ft_printf("talk to me...\n");
		len = recv(servfd, buffer, MAXLINE - 1, 0);
		if ( len < 0 ) {
			ft_perror(ERROR"recv failed"RESET);
			break;
		}
		ft_printf(YELLOW"%d bytes: '%s' from Server\n"RESET, len, buffer);
		if (!cycle_player_msgs(buffer, lobby))
			ft_perror(ERROR"handler failure"RESET);
		print_lobby(lobby);
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
int	client_reciever(int servfd, t_player *lobby)
{
	pthread_t	tid;

	(void)lobby;	// <-- this is sad
	if (pthread_create(&tid, NULL, &reciever, &servfd) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return (-1);
	}
	pthread_detach(tid);
	return (0);
}