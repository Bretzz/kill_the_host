/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   online.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:04:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 01:13:33 by totommi          ###   ########.fr       */
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

/* DB MANAGEMENT */

int		parse_msg_string(const char *msg);
int		one_player_action(const char *msg, t_player *lobby);
int		cycle_player_msgs(char *msg, t_player *lobby);

void	kill_player(const char *msg, t_player *lobby);
void	update_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);
void	new_player(const char *msg, t_player *lobby);

#endif