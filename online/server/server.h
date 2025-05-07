/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:35:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 02:37:52 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/* WARNING: we need to catch the 'we are dead' signal from the 'game' so
that every thread can exit cleanly. */

# include "../online.h"
# include <pthread.h>

typedef struct s_player_wrapper
{
	int			socket;
	pthrerad_t	tid;
}				t_player_wrapper;

pthread_t	server_reciever(int listfd, t_player *lobby);

#endif