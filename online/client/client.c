/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:02:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 01:17:28 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"

/* The client is a bit trickier. First Binds a socket to
addrin from the SERVER_ONLY... that's it, you talk and
listen from that. */

/* ft_memset(serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr->sin_family = AF_INET;
	serveraddr->sin_port = htons ( MYPORT );
	serveraddr->sin_addr.s_addr = (in_addr_t)inet_addr(servip); //192.168.1.5 //INADDR_ANY // ip_to_uns crash on macOS
	lobby[HOST].online = serveraddr; */

/* Binding UDP socket to only recieve from MYPORT and
the ip passed.
RETURNS: the bound socket, -1 on error */
static int bind_to_server(const char *servip)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
    int					servfd;
	struct sockaddr_in	*serveraddr;

	serveraddr = malloc(sizeof(struct sockaddr_in));
	if (serveraddr == NULL)
	{
		ft_perror(ERROR"malloc failure"RESET);
		return (-1);
	}
	lobby[HOST].online = serveraddr;
	if ((servfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_printf(LOG"servfd is %d\n"RESET, servfd);
	ft_memset(serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr->sin_family = AF_INET;
	serveraddr->sin_port = htons ( PORT_2 );
	serveraddr->sin_addr.s_addr = (in_addr_t)inet_addr(servip); //192.168.1.5 //INADDR_ANY // ip_to_uns crash on macOS
	if (bind(servfd, (struct sockaddr *)serveraddr, sizeof(struct sockaddr)))
	{
		ft_perror(ERROR"bind failure"RESET);
		return (-1);
	}
	serveraddr->sin_port = htons ( PORT_1 );
	return (servfd);
}

/* Acknowledgment procedure with the server.
	1. send signature + new to server
	2. recieve lobby stats */
static int	serv_ack(int servfd, t_player *lobby)
{
	char	buffer[MAXLINE + 1];

	ft_memset(buffer, 0, sizeof(buffer));
	//player signature name:ip
	buffer_player_action(lobby[PLAYER], "new", buffer);

	ft_printf(YELLOW"[test] sending '%s' to server%s\n", buffer, RESET);

	//send test
	if (sendto(servfd, buffer, ft_strlen(buffer), 0, (struct sockaddr *)lobby[HOST].online, sizeof(struct sockaddr)) < 0)
	{
		ft_perror(ERROR"sendto failure"RESET);
		return (-1);
	}

	ft_memset(buffer, 0, sizeof(buffer));
	// recieving server data name:ip (ip defaults to 'host')
	if (recvfrom(servfd, buffer, MAXLINE, 0, NULL, 0) < 0)	// <-- no need to see who is sending stuff, buond ip only to server ip
	{
		ft_perror(ERROR"recvfrom failed"RESET);
		return (-1);
	}

	ft_printf(YELLOW"[test] recieved '%s' from server%s\n", buffer, RESET);

	// getting lobby stats from server
	if (!cycle_player_msgs(buffer, lobby))
	{
		ft_printfd(STDERR_FILENO, ERROR"corrupted message%s\n", RESET);
		return (-1);
	}
	ft_printf(CONNECT"connection accepted!!!%s\n", RESET);
	return (0);
}

/* writing personal NAME and IP into the lobby database */
static int	my_data_init(t_player *lobby, char *env[])
{
	if (lobby == NULL)
		return (0);
	ft_strlcpy(lobby[PLAYER].ip, get_locl_ip(env), 16);
	ft_strlcpy(lobby[PLAYER].name, get_my_name(env), 43);
	print_lobby(lobby);
	ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	return (1);
}

/* returns 0 on error, the socket to write onto.
NOTE: the thread is detached. goes his way */
int	client_routine(t_player *lobby, char *envp[])
{
	int	servfd;

	if (!ft_strcmp("ip-not-found", get_serv_ip(envp)))
	{
		ft_printfd(STDERR_FILENO, ERROR"missing server ip:%s env variable not found\n", RESET);
		return (-1);
	}
	if (!my_data_init(lobby, envp))
		return (-1);
	ft_printf(LOG">data init ok...%s\n", RESET);
	servfd = bind_to_server(get_serv_ip(envp));
	if (servfd < 0)
		return (-1);
	ft_printf(LOG">testing connection... (socket %d)%s\n", servfd, RESET);
	if (serv_ack(servfd, lobby) < 0)
		return (close(servfd), -1);
	ft_printf(LOG">connection approved...%s\n", RESET);
	if (client_reciever(servfd, lobby) < 0)
		return (close(servfd), -1);
	usleep(1000);
	print_lobby(lobby);
	// ft_printf(LOG">reciever started%s\n", RESET);
	// ft_printf(LOG">client started on tid: %u%s\n", servtid, RESET);
	return (servfd);
}
