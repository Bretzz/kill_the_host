/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:02:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 23:13:01 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"

/* Try enstauring a TCP connection with the ip passed
RETURNS: the socket returned by connect(3), -1 on error */
int connect_to_server(const char *servip)
{
    int		servfd;
	struct sockaddr_in serveraddr;

	if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons ( MYPORT );
	serveraddr.sin_addr.s_addr = (in_addr_t)ip_to_uns(servip); //192.168.1.5 //INADDR_ANY
	if (connect(servfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)))
	{
		ft_perror(ERROR"connection failed"RESET);
		return (-1);
	}
	ft_printf(GREEN"connection accepted!!!\n"RESET);
	return (servfd);
}

/* return -1 on error, 0 on correct execution */
int	test_connection(int servfd, t_player *lobby)
{
	char	buffer[MAXLINE];

	//player signature name:ip
	ft_memset(buffer, 0, 30);
	ft_strlcpy(buffer, lobby[1].name, 11);
	ft_strlcat(buffer, ":", ft_strlen(buffer) + 2);
	ft_strlcat(buffer, lobby[1].ip, ft_strlen(buffer) + 16);

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
		ft_perror(ERROR"corrupted message"RESET);
		return (-1);
	}
	return (0);
}

/* lobby[0] = host, lobby[1] = player */
int	my_data_init(t_player *lobby, char *env[])
{
	if (lobby == NULL)
		return (0);
	// ft_strlcpy(lobby[0].ip, get_serv_ip(env), 16);
	ft_strlcpy(lobby[1].ip, get_locl_ip(env), 16);
	ft_strlcpy(lobby[1].name, get_my_name(env), 43);
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
	my_data_init(lobby, env);
	servfd = connect_to_server(get_serv_ip(env));
	if (servfd < 0)
		return (-1);
	if (test_connection(servfd, lobby) < 0)
		return (-1);
	if (client_reciever(servfd, lobby) < 0)
		return (-1);
	return (servfd);
}
