/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:03:05 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 22:45:02 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/* instaurate connection -> send signature name:ip -> wait for lobby update -> initialize lobby */
/* split thread that listen from server and updates the struct accordingly */

/* EXPECTED MSG STRINGS FROM SERVER:
'name:ip:pos:tar:action'
NOTE: the semicolons (':') are MANDATORY, even if the fields are empty, e.g: 'pippo:8.8.8.8:::update'
so there will always be at least 4 semicolons in each msg
(future implementation of escapes to protect msg-inflation ;P)*/

# include "online.h"
# include <errno.h>

int		client_reciever(int servfd, t_player *lobby);

/* DB MANAGEMENT */

int		parse_msg_string(const char *msg);
int		one_player_action(const char *msg, t_player *lobby);
int		cycle_player_msgs(char *msg, t_player *lobby);

void	kill_player(const char *msg, t_player *lobby);
void	update_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);
void	new_player(const char *msg, t_player *lobby);

#endif 