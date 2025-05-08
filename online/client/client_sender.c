/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:51:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 23:11:19 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"

static void	staitc_mutex_init(pthread_mutex_t *mutex)
{
	pthread_mutex_t	dead;

	ft_memset(&dead, 0, sizeof(pthread_mutex_t));
	if (!ft_memcmp(mutex, &dead, sizeof(pthread_mutex_t)))
		pthread_mutex_init(mutex, NULL);
}

/* -1 error, 0 ok */
/* !!! NEED MUTEX !!! */
int	client_sender(int servfd, void *buffer, size_t size)
{
	t_player *const			lobby = lbb_get_ptr(NULL);
	static pthread_mutex_t	mutex;

	staitc_mutex_init(&mutex);
	ft_printf(YELLOW"sending '%s' to server%s\n", buffer, RESET);
	pthread_mutex_lock(&mutex);
	if (sendto(servfd, buffer, size, 0, lobby[HOST].online, sizeof(struct sockaddr)) < 0)
	{
		ft_perror(ERROR"send failure"RESET);
		return (pthread_mutex_unlock(&mutex), -1);
	}
	return (pthread_mutex_unlock(&mutex), 0);
}
