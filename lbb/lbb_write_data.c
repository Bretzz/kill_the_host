/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_write_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:16:46 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 02:11:08 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

int	lbb_add_player(const char *msg);
int	lbb_update_player(const char *msg);

/* takes a msg-string as parameter.
adds the data of the player found (if there's any empty slot in the lobby).
RETURNS: 1 if data was written successfully, 0 if msg is NULL or lobby is full. */
int	lbb_add_player(const char *msg)
{
	int	slot;

	if (msg == NULL)
		return (0);
	slot = lbb_next_free_slot();
	if (slot < 0)
		return (0);
	msg_get_name(msg, g_lobby[slot].name);
	msg_get_ip(msg, g_lobby[slot].ip);
	msg_get_pos(msg, g_lobby[slot].pos);
	msg_get_tar(msg, g_lobby[slot].tar);
	return (1);
}

/* takes a msg-string as parameter.
updates the data of the player found.
RETURNS: 1 if data was written successfully, 0 if the player wasn't found */
int	lbb_update_player(const char *msg)
{
	int		index;

	if (msg == NULL)
		return (0);
	index = lbb_get_index(msg);
	msg_get_pos(msg, g_lobby[index].pos);
	msg_get_tar(msg, g_lobby[index].tar);
	return (1);
}
