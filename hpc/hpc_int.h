/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:51:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 12:04:43 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Host Punch internal header */

#ifndef HPC_INT_H
# define HPC_INT_H

# include "config.h"
# include "libft.h"
# include "lbb.h"
# include "msg.h"
# include <pthread.h>

/* SENDERS */

int				client_sender(int servfd, void *buffer, size_t size);
int				server_sender(int socket, char *buffer, void *addr, char flag);

/* UTILS */

int				ft_perror(const char *string);
unsigned int	ip_to_uns(const char *ip);

/* PRINTERS */

void			print_player(t_player player);
void			print_lobby(t_player *lobby);
void			print_quick_lobby(t_player *lobby);

/* ENV INTERFACE */

char			*get_locl_ip(char **env);
char			*get_serv_ip(char **env);
char			*get_my_name(char **env);
int				make_him_host(char *ip, char **env);

#endif