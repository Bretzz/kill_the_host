/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:34:21 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 02:06:05 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

/* Spawns a 'listener-thread' that listen for connect call
from other ips, if one si accept(3)'d spawn another thread
that listen on that one. All the 'personal listeners' thread
are detached. The listener's pid is returned
-1 on error */

/* binds a socket to MYPORT and starts listening to it.
RETURNS: the socket to listen from, -1 on error. */
static int	open_the_ears(void)
{
	struct	sockaddr_in serveraddr;
	int 	listfd;

	if ((listfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons ( MYPORT );
	serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
	if (bind(listfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)))
	{
		ft_perror(ERROR"bind failure"RESET);
		return (-1);
	}
	if (listen(listfd, MAXPLAYERS))
	{
		ft_perror(ERROR"listen failure"RESET);
		return (-1);
	}
	return (listfd);
}

static int	my_data_init(t_player *lobby, char *env[])
{
	unsigned int	i;

	if (lobby == NULL)
		return (0);
	ft_strlcpy(lobby[HOST].name, get_my_name(env), 43);
	ft_strlcpy(lobby[HOST].ip, get_locl_ip(env), 16);
	i = 0;
	while (i < MAXPLAYERS)
	{
		lobby[i].online = (t_wrapper *)malloc(sizeof(t_wrapper));
		if (lobby[i].online == NULL)
			return (0);
		ft_memset(lobby[i].online, 0, sizeof(t_wrapper));
		i++;
	}
	print_lobby(lobby);
	ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	return (1);
}

/* each player has his 'online' pointer assigned.
RETURNS: the tid' of the listener-thred, 0 on error */
pthread_t	server_routine(t_player *lobby, char *env[])
{
	t_wrapper	*host;

	if (!my_data_init(lobby, env))
		return ((pthread_t)0);
	host = lobby->online;	// wrapper of the player[0]
	host->socket = open_the_ears();
	if (host->socket < 0)
		return ((pthread_t)0);
	ft_printf(LOG">starting server on %d%s\n", host->socket, RESET);
	host->tid = server_reciever(host->socket, lobby);
	if (host->tid == 0)
		return (close(host->socket), (pthread_t)0);
	ft_printf(LOG">server started on tid: %u%s\n", host->tid, RESET);
	return (host->tid);
}
