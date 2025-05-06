/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_reciever.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:48:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 00:10:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

static void	*reciever(void *arg)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	struct sockaddr_in	clientaddr;
	int					listfd;
	int					connfd;

	listfd = *(int *)arg;
	if (lobby == NULL)
	{
		ft_printfd(STDERR_FILENO, ERROR"server reciever:%s lobby not initialized\n", RESET);
		return (NULL);
	}
	while (!0)
	{
		while (lbb_player_count() >= MAXPLAYERS)
			usleep(1000);
		ft_memset(&clientaddr, 0, sizeof(struct sockaddr_in));
		if ((connfd = accept(listfd, (struct sockaddr *)&clientaddr, NULL)) < 0)
			ft_perror(ERROR"accept failed"RESET);
		else
			ft_printf(GREEN"connection accepted!\n"RESET);
		// spawn the private_reciever()
	}
	close(listfd);
	return(NULL);
}

/* Spawns a thread that listen to clients that want to connect */
pthread_t	server_reciever(int listfd, t_player *lobby)
{
	pthread_t	tid;

	(void)lobby;	// <-- this is sad
	if (pthread_create(&tid, NULL, &reciever, &listfd) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return (-1);
	}
	return (tid);
}
