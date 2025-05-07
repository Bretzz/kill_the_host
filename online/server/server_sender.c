/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:45:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 23:23:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "server.h"

/* -1 error, 0 ok */
/* sends the string to all the clients, if the string is a msg-string
the player with same signature (name:ip) as the first msg will
be avoided. */
int	server_sender(t_player *lobby, void *buffer, size_t size)
{
	const int		sender_slot = lbb_get_index(buffer);
	t_wrapper		*wrapper;
	int				i;

	ft_printf(GREEN"sending '%s' to Clients (from: %s)%s\n", buffer, lobby[sender_slot].name, RESET);
	i = 1;
	while (i < MAXPLAYERS)
	{
		wrapper = lobby[i].online;
		if (lbb_is_alive(lobby[i]) && i != sender_slot)
		{
			if (send(wrapper->socket, buffer, size, 0) < 0)
			{
				ft_perror(ERROR"send failure"RESET);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
