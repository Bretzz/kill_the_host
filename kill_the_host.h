/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_the_host.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:51:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 19:38:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILL_THE_HOST_H
# define KILL_THE_HOST_H

# include "libft.h"
# include "lbb.h"
# include <pthread.h>

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
# define WARN "\033[48;5;229m"
# define ERROR "\033[0;41m"
# define STATS "\033[0;34m"
# define KILL "\033[0;101m"
# define LISTEN "\033[0;101m"
# define CONNECT "\033[0;42m"

/* GAME */

int	minigame(int *index, int *socket, void *thread);

/* MAP */

char	**handle_map(char *s);

/* CLIENT */

int	client_routine(pthread_t *tid, char *envp[]);
int	client_sender(int servfd, void *buffer, size_t size);

/* SERVER */

int	server_routine(pthread_t *tid, char *envp[]);
int server_sender(int socket, char *buffer, void *addr, char flag);


pthread_t	get_me_online(int *index, int *socket, char *envp[]);

/* UTILS */

int				ft_perror(const char *string);
void			free_mtx(void **mtx);
unsigned int	ip_to_uns(const char *ip);
int				ft_chrnum(const char *s, int c);

void			print_player(t_player player);
void 			print_lobby(t_player *lobby);
void			print_quick_lobby(t_player *lobby);

/* ENV INTERFACE */

char	*get_locl_ip(char **env);
char	*get_serv_ip(char **env);
char	*get_my_name(char **env);
int	make_him_host(char *ip, char **env);

#endif