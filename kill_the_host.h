/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_the_host.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:51:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 02:43:54 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILL_THE_HOST_H
# define KILL_THE_HOST_H

# include "libft.h"
# include "lbb.h"

//colors
# define BOLD "\033[1m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# define LOG "\033[0;36m"
# define ERROR "\033[0;41m"
# define STATS "\033[0;34m"
# define KILL "\033[0;101m"
# define LISTEN "\033[0;101m"
# define HOSTLOG "\033[0;43m"

/* CLIENT */

int			client_routine(t_player *lobby, char *env[]);

/* SERVER */

int	server_routine(t_player *lobby, char *env[]);

/* UTILS */

int				ft_perror(const char *string);
void			free_mtx(void **mtx);
unsigned int	ip_to_uns(const char *ip);

void			print_player(t_player player);
void 			print_lobby(t_player *lobby);

/* ENV INTERFACE */

char	*get_locl_ip(char **env);
char	*get_serv_ip(char **env);
char	*get_my_name(char **env);

#endif