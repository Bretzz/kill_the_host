/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_reciever.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:48:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 00:11:11 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

static int	handshake(int connfd, t_player *lobby)
{
	char	buffer[MAXLINE];

	ft_memset(buffer, 0, sizeof(buffer));
	if (recv(connfd, buffer, MAXLINE, 0) < 0)
	{
		ft_perror(ERROR"recv failure"RESET);
		return (0);
	}
	
	ft_printf(YELLOW"[handshake] recv '%s' from client%s\n", buffer, RESET);

	if (!cycle_player_msgs(buffer, lobby))
	{
		ft_perror(ERROR"corrupted message"RESET);
		return (0);
	}

	// telling the lobby the new player is here
	if (server_sender(lobby, buffer, ft_strlen(buffer)) < 0)
		return (0);

	// telling the player were the lobby is
	buffer_lobby_action(lobby, "new", buffer);

	ft_printf(YELLOW"[handshake] send '%s' to client%s\n", buffer, RESET);

	if (send(connfd, buffer, MAXLINE, 0) < 0)
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
	size_t						len;

	connfd = *(int *)arg;
	if (!handshake(connfd, lobby))
		return (close(connfd), NULL);
	ft_printf(LOG">handshake completed successuflly%s\n", RESET);
	while (!0)
	{
		if (!lbb_is_alive(lobby[HOST]))	// temporary way of clean kill
		{
			ft_printfd(STDERR_FILENO, HOSTLOG"host died%s\n", RESET);
			break ;
		}
		ft_memset(buffer, 0, sizeof(buffer));
		if ((len = recv(connfd, buffer, MAXLINE, 0)) < 0)
		{
			ft_perror(ERROR"recv failure"RESET);
			break ;
		}
		ft_printf(YELLOW"%d bytes: '%s' from Client\n"RESET, len, buffer);
		if (!cycle_player_msgs(buffer, lobby))
		{
			ft_perror(ERROR"handler failure"RESET);
			break ;
		}
		// chaos
		// ft_printf(BLUE"== = = == == =\n");
		// print_quick_lobby(lobby);
		// ft_printf(RESET);
		if (server_sender(lobby, buffer, ft_strlen(buffer) * sizeof(char)) < 0)
			break ;
	}
	// client:10.12.2.7:1_1_1::update
	ft_printf(LOG"private listener shutting down\n"RESET);
	return (close(connfd), NULL);
}

static void	*reciever(void *arg)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	t_wrapper			*wrapper;
	int					listfd;
	// int					connfd;
	// int					slot;

	// ft_printf(LOG">reciever is starting...%s\n", RESET);
	listfd = *(int *)arg;
	if (lobby == NULL)
	{
		ft_printfd(STDERR_FILENO, ERROR"server reciever:%s lobby not initialized\n", RESET);
		return (NULL);
	}
	while (!0)
	{
		while (lbb_player_count() >= MAXPLAYERS)
			usleep(10000);
		if (!lbb_is_alive(lobby[HOST]))	// temporary way of clean kill
		{
			ft_printfd(STDERR_FILENO, HOSTLOG"host died%s\n", RESET);
			break ;
		}
		wrapper = lobby[lbb_next_free_slot()].online;
		ft_printf(LISTEN">listening on %d...%s\n", listfd, RESET);
		wrapper->socket = accept(listfd, NULL, NULL);	// we can get info on the dude without the NULLS
		if (wrapper->socket < 0)
		{
			ft_perror(ERROR"accept failed"RESET);
			return(close(listfd), NULL);
		}
		else
			ft_printf(CONNECT"connection accepted!%s\n", RESET);
		if (pthread_create(&wrapper->tid, NULL, &private_reciever, &wrapper->socket) < 0)
			ft_perror(ERROR"reciever launch failed"RESET);
		pthread_detach(wrapper->tid);
	}
	ft_printf(LOG"server shutting down\n"RESET);
	return(close(listfd), NULL);
}

/* Spawns a thread that listen to clients that want to connect */
/* sockets is a pointer to MAXPLAYERS ints where sockets will be stored */
pthread_t	server_reciever(int listfd, t_player *lobby)
{
	pthread_t	tid;

	(void)lobby;	// <-- this is sad
	if (listfd != *(int *)(lobby->online))
	{
		ft_printfd(STDERR_FILENO, ERROR"reciever failure:%s socket corrupted", RESET);
		return (0);
	}
	if (pthread_create(&tid, NULL, &reciever, lobby->online) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return (0);
	}
	return (tid);
}
