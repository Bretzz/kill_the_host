/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_read_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:54:44 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 02:09:18 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

int	lbb_get_index(const char *msg);
int	lbb_next_free_slot();

/* Takes a msg-string, as parameter.
RETURNS: the index of the player matching name:ip, -1 if not found.
TODO: also just pass name/ip as parameter. */
int	lbb_get_index(const char *msg)
{
	char	msg_name[43];
	char	msg_ip[16];
	int		i;

	if (msg == NULL)
		return (-1);
	msg_get_name(msg, msg_name);
	msg_get_ip(msg, msg_ip);
	i = 0;
	while (i < MAXPLAYERS)
	{
		if (!strcmp(msg_name, g_lobby[i].name)
			&& !strcmp(msg_ip, g_lobby[i].ip))
			return (i);
		i++;
	}
	return (-1);
}

/* RETURNS: the next empty slot of the lobby, -1 if lobby is full.*/
int	lbb_next_free_slot()
{
	int	slot;

	slot = 0;
	while (slot < MAXPLAYERS)
	{
		if (g_lobby[slot].ip[0] == '\0')
			return (slot);
		slot++;
	}
	return (-1);
}
