/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_udp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:07:53 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 15:55:41 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"

// int main( void )
// {
//     int fd;
//     if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
//         perror("socket failed");
//         return 1;
//     }

//     struct sockaddr_in serveraddr;
//     memset( &serveraddr, 0, sizeof(serveraddr) );
//     serveraddr.sin_family = AF_INET;
//     serveraddr.sin_port = htons( 50037 );              
//     serveraddr.sin_addr.s_addr = htonl( 0x7f000001 );  //my_pc=0x0a0c020b //loclhost=0x7f000001

//     for ( int i = 0; i < 4; i++ ) {
//         if (sendto( fd, "hello", 5, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
//             perror( "sendto failed" );
//             break;
//         }
//         printf( "message sent\n" );
//     }

//     close( fd );
// }

/* Try enstauring a TCP connection with the ip passed
RETURNS: the socket returned by connect(3), -1 on error */
static int connect_to_server(const char *servip)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	struct	sockaddr_in	*serveraddr;
    int					servfd;

	if ((servfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	serveraddr = malloc(sizeof(struct	sockaddr_in));
	if (serveraddr == NULL)
	{
		ft_perror(ERROR"malloc failure"RESET);
		return (-1);
	}
	ft_memset(serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr->sin_family = AF_INET;
	serveraddr->sin_port = htons ( MYPORT );
	serveraddr->sin_addr.s_addr = (in_addr_t)inet_addr(servip); //192.168.1.5 //INADDR_ANY // ip_to_uns crash on macOS
	lobby[HOST].online = serveraddr;
	// if (connect(servfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)))
	// {
	// 	ft_perror(ERROR"connection failed"RESET);
	// 	return (-1);
	// }
	// ft_printf(CONNECT"connection accepted!!!%s\n", RESET);
	return (servfd);
}

/* return -1 on error, 0 on correct execution */
static int	test_connection(int servfd, t_player *lobby)
{
	char	buffer[MAXLINE + 1];
	socklen_t	len = sizeof(struct sockaddr);

	ft_memset(buffer, 0, sizeof(buffer));
	//player signature name:ip
	buffer_player_action(lobby[PLAYER], "new", buffer);

	ft_printf(YELLOW"[test] sending '%s' to server%s\n", buffer, RESET);

	//send test
	if (sendto(servfd, buffer, ft_strlen(buffer), 0, (struct sockaddr *)lobby[HOST].online, sizeof(struct sockaddr_in)) < 0 ) {
		ft_perror(ERROR"sendto failed"RESET);
		return (-1);
	}
	// if (send(servfd, buffer, ft_strlen(buffer), 0) < 0)
	// {
	// 	ft_perror(ERROR"send failure"RESET);
	// 	return (-1);
	// }

	ft_memset(buffer, 0, sizeof(buffer));
	// recieving server data name:ip (ip defaults to 'host')
	if (recvfrom(servfd, buffer, MAXLINE, 0, (struct sockaddr *)lobby[HOST].online, &len) < 0)
	{
		ft_perror(ERROR"recv failed"RESET);
		return (-1);
	}

	ft_printf(YELLOW"[test] recieved '%s' from server%s\n", buffer, RESET);

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
	print_lobby(lobby);
	ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	return (1);
}

/* returns 0 on error, the tid of the reciever-thread
to join before exit.
NOTE: the socket is stored in *(int *)lobby->online */
pthread_t	client_udp_routine(t_player *lobby, char *env[])
{
	pthread_t	servtid;
	int			servfd;

	if (!ft_strcmp("ip-not-found", get_serv_ip(env)))
	{
		ft_printfd(STDERR_FILENO, ERROR"missing server ip:%s env variable not found\n", RESET);
		return ((pthread_t)0);
	}
	if (!my_data_init(lobby, env))
		return ((pthread_t)0);
	ft_printf(LOG">data init ok...%s\n", RESET);
	servfd = connect_to_server(get_serv_ip(env));
	if (servfd < 0)
		return ((pthread_t)0);
	ft_printf(LOG">testing connection...%s\n", RESET);
	if (test_connection(servfd, lobby) < 0)
		return (close(servfd), (pthread_t)0);
	ft_printf(LOG">connection approved...%s\n", RESET);
	print_lobby(lobby);
	ft_memcpy(&lobby->online, &servfd, sizeof(int));
	servtid = client_reciever(servfd, lobby);
	if (servtid == 0)
		return (close(servfd), (pthread_t)0);
	// ft_printf(LOG">reciever started%s\n", RESET);
	// ft_printf(LOG">client started on tid: %u%s\n", servtid, RESET);
	return (servtid);
}
