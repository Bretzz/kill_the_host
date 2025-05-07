/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:02:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 02:48:50 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"

/* Try enstauring a TCP connection with the ip passed
RETURNS: the socket returned by connect(3), -1 on error */
static int connect_to_server(const char *servip)
{
    int		servfd;
	struct	sockaddr_in serveraddr;

	if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons ( MYPORT );
	serveraddr.sin_addr.s_addr = (in_addr_t)inet_addr(servip); //192.168.1.5 //INADDR_ANY // ip_to_uns crash on macOS
	if (connect(servfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)))
	{
		ft_perror(ERROR"connection failed"RESET);
		return (-1);
	}
	ft_printf(GREEN"connection accepted!!!\n"RESET);
	return (servfd);
}

/* return -1 on error, 0 on correct execution */
static int	test_connection(int servfd, t_player *lobby)
{
	char	buffer[MAXLINE];

	//player signature name:ip
	ft_memset(buffer, 0, MAXLINE);
	ft_strlcpy(buffer, lobby[PLAYER].name, MAXLINE);
	ft_strlcat(buffer, ":", MAXLINE);
	ft_strlcat(buffer, lobby[PLAYER].ip, MAXLINE);
	ft_strlcat(buffer, ":", MAXLINE);
	ft_strlcat(buffer, "new", MAXLINE);

	//send test
	if (send(servfd, buffer, 30, 0) < 0)
	{
		ft_perror(ERROR"send failure"RESET);
		return (-1);
	}

	// recieving server data name:ip (ip defaults to 'host')
	if (recv(servfd, buffer, MAXLINE - 1, 0) < 0)
	{
		ft_perror(ERROR"recv failed"RESET);
		return (-1);
	}

	// getting lobby stats from server
	if (!cycle_player_msgs(buffer, lobby))
	{
		ft_printfd(STDERR_FILENO, ERROR"corrupted message%s\n", RESET);
		return (-1);
	}
	return (0);
}

/* lobby[0] = host, lobby[1] = player */
static int	my_data_init(t_player *lobby, char *env[])
{
	if (lobby == NULL)
		return (0);
	// ft_strlcpy(lobby[0].ip, get_serv_ip(env), 16);
	ft_strlcpy(lobby[PLAYER].ip, get_locl_ip(env), 16);
	ft_strlcpy(lobby[PLAYER].name, get_my_name(env), 43);
	return (1);
}

/* returns -1 on error, the fd of the socket
to talk with the server on correct execution */
int	client_routine(t_player *lobby, char *env[])
{
	int	servfd;

	if (!ft_strcmp("ip-not-found", get_serv_ip(env)))
	{
		ft_printfd(STDERR_FILENO, ERROR"missing server ip:%s env variable not found\n", RESET);
		return (-1);
	}
	if (!my_data_init(lobby, env))
		return (-1);
	ft_printf(LOG"data init ok...%s\n", RESET);
	servfd = connect_to_server(get_serv_ip(env));
	if (servfd < 0)
		return (-1);
	ft_printf(LOG"testing connection...%s\n", RESET);
	if (test_connection(servfd, lobby) < 0)
		return (close(servfd), -1);
	ft_printf(LOG"connection approved...%s\n", RESET);
	if (client_reciever(servfd, lobby) < 0)
		return (close(servfd), -1);
	ft_printf(LOG"reciever started%s\n", RESET);
	return (servfd);
}
