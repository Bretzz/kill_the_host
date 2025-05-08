/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:35:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 15:17:42 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/* WARNING: we need to catch the 'we are dead' signal from the 'game' so
that every thread can exit cleanly. */

# include "../online.h"
# include <pthread.h>

typedef struct s_wrapper
{
	int			socket;
	pthread_t	tid;
}				t_wrapper;

pthread_t	server_reciever(int listfd, t_player *lobby);
pthread_t	server_udp_reciever(int listfd, t_player *lobby);

int			server_sender(t_player *lobby, void *buffer, size_t size);

#endif