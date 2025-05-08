/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_reciever.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:33:11 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 01:22:33 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"
#include <pthread.h>

int	client_reciever(int servfd, t_player *lobby);

static void	*reciever(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	char			buffer[MAXLINE + 1];
	size_t			len;
	int				servfd;

	servfd = *(int *)arg;
	ft_printf(LOG">recieving on socket %d%s\n", servfd, RESET);
	while (!0)
	{
		ft_memset(buffer, 0, sizeof(buffer));
		// ft_printf("talk to me...\n");
		len = recvfrom(servfd, buffer, MAXLINE, 0, NULL, 0);
		if ( len < 0 ) {
			ft_perror(ERROR"recvfrom failed"RESET);
			break;
		}
		if (parse_msg_string(buffer) <= 0)	// really ugly
		{
			ft_printfd(STDERR_FILENO, WARN"corrupted buffer:%s '%s'\n", RESET, buffer);
			break ;
		}
		ft_printf(YELLOW"%d bytes: '%s' from Server\n"RESET, len, buffer);
		if (!cycle_player_msgs(buffer, lobby))
		{
			ft_perror(ERROR"handler failure"RESET);
			break ;
		}
		// // chaos
		// ft_printf(BLUE"== = = == == =\n");
		// print_quick_lobby(lobby);
		// ft_printf(RESET);
	}
	close(servfd);
	return (NULL);
}
// if (handle_client_players(buffer, recenv) < 0)
// {
// 	ft_printf(HOSTLOG"A NEW HOST WILL RISE%s\n", RESET);
// 	return (close(recenv->player[0].socket), free(recenv), NULL);
// }

/* Spawns a thread that listen to the server for updates on the players */
int	client_reciever(int servfd, t_player *lobby)
{
	pthread_t	tid;
	int			code;

	(void)lobby;	// <-- this is sad
	if (pthread_create(&tid, NULL, &reciever, &servfd) < 0)
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
