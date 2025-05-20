/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:42:19 by totommi           #+#    #+#             */
/*   Updated: 2025/05/20 23:42:27 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "msg.h"
#include "boring_header.h"
// #include <sys/wait.h>
#include <pthread.h>

int	main(int argc, char *argv[], char *envp[])
{	
	(void)argc; (void)argv; (void)envp;
	// if (argc < 2)
	// 	return (1);
	if (lbb_init() == NULL)
		return (1);
	ft_printf(LOG"THIS THING CRASHES: right now each player has his online stuff in 'server' mode but the message aren't beingn rebound to anyone, so it's useless, he just listens.\nthe client is almost done, we need the send-message part then, thhe ones that qquits cleanly on host's death (also for server), then all good%s\n", RESET);
	int			socket;
	int			index;
	// #include <signal.h>
	// sigaction(SIGUSR1, NULL, NULL);
	pthread_t	tid = get_me_online(&index, &socket, envp);
	usleep(1000);
	ft_printf(">START GAME\n");
	usleep(1000);
	hpc_free(&socket, &index, &tid);
	return (0);
}
