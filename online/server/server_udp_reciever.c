/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_udp_reciever.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:02:55 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 15:55:00 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

// int main( void )
// {
//     int fd;
//     if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
//         ft_perror( "socket failed" );
//         return 1;
//     }

//     struct sockaddr_in serveraddr;
//     memset( &serveraddr, 0, sizeof(serveraddr) );
//     serveraddr.sin_family = AF_INET;
//     serveraddr.sin_port = htons( 50037 );
//     serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );

//     if ( bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
//         ft_perror( "bind failed" );
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

// struct	sockaddr_in	*clientaddr;


/* ! ! ! MUTEX THE WHOLE LOBBY WHILE DOING THIS ! ! ! */
static int	handshake(int recvfd, t_player *lobby)
{
	char				buffer[MAXLINE];
	struct sockaddr_in	*clientaddr;
	socklen_t	len = sizeof(struct sockaddr);

	clientaddr = malloc(sizeof(struct	sockaddr_in));
	if (clientaddr == NULL)
	{
		ft_perror(ERROR"malloc failure"RESET);
		return (-1);
	}
	ft_memset(clientaddr, 0, sizeof(struct sockaddr_in));
	ft_memset(buffer, 0, sizeof(buffer));
	if (recvfrom(recvfd, buffer, MAXLINE, 0, (struct sockaddr *)clientaddr, &len) < 0)
	{
		ft_perror(ERROR"recv failure"RESET);
		return (0);
	}
	ft_printf("new client!!!\n");	// <-- need welcome routine
	lobby[lbb_next_free_slot()].online = clientaddr;	// <-- mutex needed to sink with cycle_player_msg
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

	if (sendto(recvfd, buffer, MAXLINE, 0, (struct sockaddr *)clientaddr, sizeof(struct sockaddr)) < 0)
	{
		ft_perror(ERROR"send failure"RESET);
		return (0);
	}
	// clear the lobby slot (also freeing pointer)
	return (1);
}

static void	*reciever(void *arg)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	int					recvfd;
	char				buffer[MAXLINE];
	// int					connfd;
	// int					slot;

	// ft_printf(LOG">reciever is starting...%s\n", RESET);
	recvfd = *(int *)arg;
	if (lobby == NULL)
	{
		ft_printfd(STDERR_FILENO, ERROR"server reciever:%s lobby not initialized\n", RESET);
		return (NULL);
	}
	if (!handshake(recvfd, lobby))
		return (close(recvfd), NULL);
	ft_printf(LOG">handshake completed successuflly%s\n", RESET);
	while (!0)
	{
		while (lbb_player_count() >= MAXPLAYERS)
			usleep(10000);
		if (!lbb_is_alive(lobby[HOST]))	// temporary way of clean kill
		{
			ft_printfd(STDERR_FILENO, HOSTLOG"host died%s\n", RESET);
			break ;
		}
		ft_memset(buffer, 0, sizeof(buffer));
		int length = recvfrom( recvfd, buffer, sizeof(buffer) - 1, 0, NULL, 0 );
		if ( length < 0 ) {
			ft_perror(ERROR"recvfrom failed"RESET);
			break;
		}
		buffer[length] = '\0';
		ft_printf( "%d bytes: '%s'\n", length, buffer );
	}
	ft_printf(LOG"server shutting down\n"RESET);
	return(close(recvfd), NULL);
}

/* Spawns a thread that listen to clients that want to connect */
/* sockets is a pointer to MAXPLAYERS ints where sockets will be stored */
pthread_t	server_udp_reciever(int recvfd, t_player *lobby)
{
	pthread_t	tid;

	(void)lobby;	// <-- this is sad
	// if (recvfd != *(int *)(lobby->online))
	// {
	// 	ft_printfd(STDERR_FILENO, ERROR"reciever failure:%s socket corrupted", RESET);
	// 	return (0);
	// }
	if (pthread_create(&tid, NULL, &reciever, &recvfd) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return (0);
	}
	usleep(10);	//time to copy recvfd (UGLY)
	// ft_printf("OUT RECVD %d\n", recvfd);
	return (tid);
}