/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:34:21 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 02:44:10 by totommi          ###   ########.fr       */
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
	if (listen(listfd, 10))
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
	ft_strlcpy(lobby[HOST].ip, get_locl_ip(env), 43);
	i = 0;
	while (i < MAXPLAYERS)
	{
		lobby[i].online = (t_player_wrapper *)malloc(sizeof(t_player_wrapper))
		if (lobby[i].online == NULL)
			return (0);
		ft_memset(lobby[i].online, 0, sizeof(t_player_wrapper));
		i++;
	}
	return (1);
}

/* each player has his 'online' pointer assigned */
int	server_routine(t_player *lobby, char *env[])
{
	if (!my_data_init(lobby, env))
		return (-1);
	lobby->online->socket = open_the_ears();
	if (lobby->online->socket < 0)
		return (-1);
	lobby->online->tid = server_reciever(lobby->online->socket, lobby->online);
	if (lobby->online->tid < 0)
		return (close(lobby->online->socket), -1);
	return (lobby->online->tid);
}
