/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_reciever.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:48:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 02:29:50 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

static int	handshake(int connfd, t_player *lobby)
{
	char	buffer[MAXLINE];

	if (recv(connfd, buffer, MAXLINE) < 0)
	{
		ft_perror(ERROR"recv failure"RESET);
		return (0);
	}
	if (!cycle_player_msgs(buffer))
	{
		ft_perror(ERROR"corrupted message"RESET);
		return (0);
	}
	lbb_get_lobby_stats(lobby, buffer);
	if (send(connfd, buffer, MAXLINE) < 0)
	{
		ft_perror(ERROR"send failure"RESET);
		return (0);
	}
	return (1);
}

/* passed the wrapper to the precise element of the array of wrappers */
static void	*private_reciever(void *arg)
{
	t_player *const				lobby = lbb_get_ptr(NULL);
	char						buffer[MAXLINE];
	int							connfd;

	connfd = *(int *)arg;
	if (!handshake(connfd, lobby))
		return (close(connfd), NULL);
	while (!0)
	{
		if (!lbb_is_alive(lobby[HOST]))
			break ;
		if (recv(connfd, buffer, MAXLINE) < 0)
		{
			ft_perror(ERROR"recv failure"RESET);
			return (0);
		}
		if (!cycle_player_msgs(buffer))
		{
			ft_perror(ERROR"handler failure"RESET);
			return (0);
		}
	}
	close(connfd);
	return (NULL);
}

static void	*reciever(void *arg)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	int					listfd;
	int					connfd;
	int					slot;

	listfd = *(int *)arg;
	if (lobby == NULL)
	{
		ft_printfd(STDERR_FILENO, ERROR"server reciever:%s lobby not initialized\n", RESET);
		return (NULL);
	}
	while (!0)
	{
		while (lbb_player_count() >= MAXPLAYERS)
			usleep(1000);
		slot = lbb_next_free_slot();
		lobby[slot].online->socket = accept(listfd, NULL, NULL);	// we can get info on the dude without the NULLS
		if (lobby[slot].online->socket < 0)
			ft_perror(ERROR"accept failed"RESET);
		else
			ft_printf(GREEN"connection accepted!\n"RESET);
		if (pthread_create(&lobby[slot].online->tid, NULL, &private_reciever, &lobby[slot].online->socket) < 0)
			ft_perror(ERROR"reciever launch failed"RESET);
		// pthread_detach(tid);
	}
	close(listfd);
	return(NULL);
}

/* Spawns a thread that listen to clients that want to connect */
/* sockets is a pointer to MAXPLAYERS ints where sockets will be stored */
pthread_t	server_reciever(int listfd, t_player *lobby)
{
	pthread_t	tid;

	(void)lobby;	// <-- this is sad
	if (pthread_create(&tid, NULL, &reciever, &listfd) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return (-1);
	}
	return (tid);
}
