/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   online.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:04:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 22:32:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONLINE_H
# define ONLINE_H

//net libraries
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
//# include <sys/types.h>
# include <netdb.h>

# define MYPORT 42042
# define MAXLINE 1024 


/* MSG STRING MANAGEMENT */

int		parse_msg_string(const char *msg);
int		one_player_action(const char *msg, t_player *lobby);
int		cycle_player_msgs(char *msg, t_player *lobby);

char	*buffer_player_action(t_player player, const char *action, void *buffer);
char	*buffer_lobby_action(t_player *lobby, const char *action, void *buffer);

/* DB MANAGEMENT */

// void	kill_player(const char *msg, t_player *lobby);
// void	update_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);
void	new_player(const char *msg, t_player *lobby);

#endif