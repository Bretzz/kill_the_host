/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_me_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:15:22 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 14:26:14 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "online.h"

// int	make_him_host(char *ip, char **env)
// {
// 	int	i;
//
// 	if (ip == NULL || env == NULL)
// 		return (0);
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (!strncmp("SERVER_IP=", env[i], 10) && *(env[i] + 10) != '\0')
// 		{
// 			ft_memset(env[i] + 10, 0, ft_strlen(env[i] + 10));
// 			ft_memmove(env[i] + 10, ip, ft_strlen(ip));
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static void	*manager(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	t_setup *const	setup = arg;
	pthread_t		tid;
	int				code;

	while (!0)
	{
		if (*setup->socket > 2)
			close(*setup->socket);
		if (*setup->index == HOST)
		{
			ft_printf(LOG"===STARTING SERVER===\n"RESET);
			*setup->socket = server_routine(&tid, setup->envp);
		}
		else if (*setup->index == PLAYER)
		{
			ft_printf(LOG"===STARTING CLIENT===\n"RESET);
			*setup->socket = client_routine(&tid, setup->envp);
		}
		code = pthread_join(tid, NULL);
		if (code != 0)
		{
			ft_printfd(STDERR_FILENO, ERROR"join failure:%s code %d\n", RESET, code);
			*setup->index = -1;
			return (free(setup), NULL);
		}
		ft_printf(LOG">reciever closed%s\n", RESET);
		if (*setup->index < 0)	// we died (-1 set in minigame)
			return (free(setup), NULL);
		if (!ft_strcmp(get_locl_ip(setup->envp), lobby[HOST].ip))
			*setup->index = 0;
		else
			make_him_host(lobby[HOST].ip, setup->envp);	//could break
	}
}

/* Spawns the manager thread for internet connection.
Switches from client to host on kill, and changes host
if the host died. If the socket pointed by *socket gets
close(3)d, the thread starts the cleanup routine.
RETURNS: the thread to join before shutting down  */
/* HOW IT WORKS:
	1. reads the index,
	2. starts the routine & sets the socket
	3. (something changes)
		3.1 we died? return : go to 1 */
/* PLS INITIALIZE SOCKET */
pthread_t	get_me_online(int *index, int *socket, char *envp[])
{
	pthread_t	tid;
	t_setup		*setup;

	setup = malloc(sizeof(t_setup));
	if (setup == NULL)
		return (0);
	setup->index = index;
	setup->socket = socket;
	setup->envp = envp;
	if (pthread_create(&tid, NULL, &manager, setup) < 0)
	{
		ft_perror(ERROR"thread launch"RESET);
		return (0);
	}
	while (*socket < 2)
		usleep(1000);
	return (tid);
}
