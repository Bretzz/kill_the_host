/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_the_host.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:51:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 12:08:00 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILL_THE_HOST_H
# define KILL_THE_HOST_H

# include "hpc.h"
# include "libft.h"
# include <pthread.h>

/* GAME */

int	minigame(int *index, int *socket, void *thread);

/* MAP */

char	**handle_map(char *s);

/* ============= MULTIPLAYER ============= */

/* CLIENT */

int	client_sender(int servfd, void *buffer, size_t size);

/* SERVER */

int server_sender(int socket, char *buffer, void *addr, char flag);

/* THE REAL DEAL */

pthread_t	get_me_online(int *index, int *socket, char *envp[]);

#endif