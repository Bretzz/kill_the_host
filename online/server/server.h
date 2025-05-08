/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:35:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 23:02:51 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/* WARNING: we need to catch the 'we are dead' signal from the 'game' so
that every thread can exit cleanly. */

# include "../online.h"
# include <pthread.h>

/* EXTERNAL USE */

int server_sender(int socket, char *buffer, void *addr, char flag);
int	server_routine(t_player *lobby, char *envp[]);

/* INTERNAL USE */

int	server_reciever(int servfd, t_player *lobby);

#endif