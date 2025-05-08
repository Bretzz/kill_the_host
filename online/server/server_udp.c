/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_udp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:55:33 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 15:25:43 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

// int main( void )
// {
//     int fd;
//     if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
//         perror( "socket failed" );
//         return 1;
//     }

//     struct sockaddr_in serveraddr;
//     memset( &serveraddr, 0, sizeof(serveraddr) );
//     serveraddr.sin_family = AF_INET;
//     serveraddr.sin_port = htons( 50037 );
//     serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );

//     if ( bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
//         perror( "bind failed" );
//         return 1;
//     }

//     char buffer[200];
//     for ( int i = 0; i < 4; i++ ) {
//         int length = recvfrom( fd, buffer, sizeof(buffer) - 1, 0, NULL, 0 );
//         if ( length < 0 ) {
//             perror( "recvfrom failed" );
//             break;
//         }
//         buffer[length] = '\0';
//         printf( "%d bytes: '%s'\n", length, buffer );
//     }

//     close( fd );
// }

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
	int 	recvfd;

	if ((recvfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons ( MYPORT );
	serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
	if (bind(recvfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)))
	{
		ft_perror(ERROR"bind failure"RESET);
		return (-1);
	}
	return (recvfd);
}

static int	my_data_init(t_player *lobby, char *env[])
{
	// unsigned int	i;

	if (lobby == NULL)
		return (0);
	ft_strlcpy(lobby[HOST].name, get_my_name(env), 43);
	ft_strlcpy(lobby[HOST].ip, get_locl_ip(env), 16);
	// i = 0;
	// while (i < MAXPLAYERS)
	// {
	// 	lobby[i].online = (t_wrapper *)malloc(sizeof(t_wrapper));
	// 	if (lobby[i].online == NULL)
	// 		return (0);
	// 	ft_memset(lobby[i].online, 0, sizeof(t_wrapper));
	// 	i++;
	// }
	print_lobby(lobby);
	ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	return (1);
}

/* each player has his 'online' pointer assigned.
RETURNS: the tid' of the listener-thred, 0 on error */
pthread_t	server_udp_routine(t_player *lobby, char *env[])
{
	int	recvfd;
	pthread_t	tid;

	if (!my_data_init(lobby, env))
		return ((pthread_t)0);
	recvfd = open_the_ears();
	ft_memcpy(&lobby->online, &recvfd, sizeof(int));
	if (recvfd < 0)
		return ((pthread_t)0);
	ft_printf(LOG">starting server on %d%s\n", recvfd, RESET);
	tid = server_udp_reciever(recvfd, lobby);
	if (tid == 0)
		return (close(recvfd), (pthread_t)0);
	ft_printf(LOG">server started on tid: %u%s\n", tid, RESET);
	return (tid);
}

