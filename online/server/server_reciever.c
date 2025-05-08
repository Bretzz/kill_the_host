/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_reciever.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:42:13 by totommi           #+#    #+#             */
/*   Updated: 2025/05/09 01:29:58 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"
#include <pthread.h>

int	server_reciever(int servfd, t_player *lobby);

/* 0 error, 1 ok */ /* rn no selective ban on sussy behaviour */
int	who_is_there(int socket, t_player *lobby, struct sockaddr_in *addr, char *buffer)
{
	struct sockaddr_in	*personal;
	char				bluffer[MAXLINE + 1];

	// checking for corrupted message
	if (parse_msg_string(buffer) <= 0)
	{
		ft_printfd(STDERR_FILENO, ERROR"ack failed:%s currupted message\n", RESET);
		return (0);
	}

	// changing addr port and sending it to the new player
	buffer_lobby_action(lobby, "new", bluffer);
	addr->sin_port = htons ( PORT_2 );
	if (server_sender(socket, bluffer, addr, 1) < 0)
		return (0);

	// storing addr in dynamic sockaddr
	personal = malloc(sizeof(struct sockaddr_in));
	if (personal == 0)
	{
		ft_perror(ERROR"malloc failure"RESET);
		return (0);
	}
	ft_memcpy(personal, addr, sizeof(struct sockaddr_in));

	// adding new player to database
	if (one_player_action(buffer, lobby, personal) <= 0)
	{
		ft_perror(ERROR"lobby failure"RESET);
		return (free(personal), 0);
	}
	// sending the update to the rest of the lobby
	if (server_sender(socket, buffer, personal, 1) < 0)
		return (free(personal), 0);
	return (1);
}

/* checks weather the address is already in the lobby */
int	addr_in_lobby(t_player *lobby, struct sockaddr_in *addr)
{
	int	i;

	i = 1;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i])
			&& !ft_memcmp(lobby[i].online, addr,
					sizeof(struct sockaddr_in)))
			{
				return (1);
			}
		i++;
	}
	return (0);
}

/* This is awesome.
Need more parsing on what was sent?
	--> parse_msg_string()
Need different handshake provedure?
	--> who_is_there()
Need new msg interpretation?
	--> one_player_action() */
static void	*reciever(void *arg)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	char				buffer[MAXLINE + 1];
	struct sockaddr_in	addr;
	socklen_t			len;
	int					socket;

	socket = *(int *)arg;
	ft_printf(LOG">recieving on socket %d%s\n", socket, RESET);
	while (!0)
	{
		ft_memset(buffer, 0, sizeof(buffer));
		if (recvfrom(socket, buffer, MAXLINE, 0, (struct sockaddr *)&addr, &len) < 0)
		{
			ft_perror(ERROR"recvfrom failed"RESET);
			break;
		}
		if (parse_msg_string(buffer) <= 0)
		{
			ft_printfd(STDERR_FILENO, WARN"corrupted buffer:%s '%s'\n", RESET, buffer);
			continue ;
		}
		ft_printf(YELLOW"%d bytes: '%s' from Client\n"RESET, ft_strlen(buffer), buffer);
		if (ft_strnstr(buffer, ":new", sizeof(buffer))
			&& !addr_in_lobby(lobby, &addr)
			&& who_is_there(socket, lobby, &addr, buffer))
			ft_printf(CONNECT"'%z' joined the lobby%s\n", buffer, msg_name_length(buffer), RESET);
		else if (!cycle_player_msgs(buffer, lobby))
		{
			ft_perror(ERROR"handler failure"RESET);
			break ;
		}
	}
	return (close(socket), NULL);
}
// if (handle_client_players(buffer, recenv) < 0)
// {
// 	ft_printf(HOSTLOG"A NEW HOST WILL RISE%s\n", RESET);
// 	return (close(recenv->player[0].socket), free(recenv), NULL);
// }

/* Spawns a thread that listen to the everyone
and handles new connections. */
int	server_reciever(int socket, t_player *lobby)
{
	pthread_t	tid;
	int			code;

	(void)lobby;	// <-- this is sad
	if (pthread_create(&tid, NULL, &reciever, &socket) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return (-1);
	}
	code = pthread_detach(tid);
	// might need usleep
	sleep(1);
	if (code != 0)
	{
		ft_printfd(STDERR_FILENO, ERROR"detach failure:%s code %d\n", RESET, code);
		return (-1);
	}
	return (0);
}
