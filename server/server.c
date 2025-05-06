/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:34:21 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 23:53:49 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

/* Spawns a 'listener-thread' that listen for connect call
from other ips, if one si accept(3)'d spawn another thread
that listen on that one. All the 'personal listeners' thread
are detached. The listener's pid is returned
-1 on error */

static int	host_player_init(t_player *player, char **env)
{
	struct	sockaddr_in serveraddr;
	int 	listfd;
	
	if ((listfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (perror(ERROR"socket failure"RESET), -1);
	
	ft_memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons ( MYPORT );
	serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );

	if (bind(listfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)))
		return (perror(ERROR"bind failure"RESET), -1);

	if (listen(listfd, 10))
		return(perror(ERROR"listen failure"RESET), -1);
	
// 	ft_printf(LISTEN"I'm listening...%s\n", RESET);

// 	//player[0] 'host' data init
// 	ft_memmove(&player[0].ip, get_serv_ip(env), 15);
// 	ft_memmove(&player[0].name, get_my_name(env), 10);
// 	//ft_strlcat(player[0].name, "_host", ft_strlen(player[0].name) + 6);
// 	player[0].num = 0;
// 	return(listfd);
// }
}

/* binds a socket to MYPORT and starts listening to it.
RETURNS: the socket to listen from, -1 on error. */
int	open_the_ears(void)
{
	struct	sockaddr_in serveraddr;
	int 	listfd;

	if ((listfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons ( MYPORT );
	serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
	if (bind(listfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)))
	{
		ft_perror(ERROR"bind failure"RESET);
		return (-1);
	}
	if (listen(listfd, 10))
	{
		ft_perror(ERROR"listen failure"RESET);
		return (-1);
	}
	return (listfd);
}

static int	my_data_init(t_player *lobby, char *env[])
{
	if (lobby == NULL)
		return (0);
	ft_strlcpy(lobby[0].name, get_my_name(env), 43);
	ft_strlcpy(lobby[0].ip, get_locl_ip(env), 43);
	return (1);
}

pthread_t	server_routine(t_player *lobby, char *env[])
{
	int			listfd;
	pthread_t	listid;

	
	return (listid);
}