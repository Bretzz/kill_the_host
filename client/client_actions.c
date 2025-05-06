/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 22:59:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"

void	kill_player(const char *msg, t_player *lobby);
void	update_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);
void	new_player(const char *msg, t_player *lobby);

void	new_player(const char *msg, t_player *lobby)
{
	int	slot;

	slot = lbb_next_free_slot();
	if (slot < 0)
		return ;
	msg_get_name(msg, lobby[slot].name);
	msg_get_ip(msg, lobby[slot].ip);
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
}

void	kill_player(const char *msg, t_player *lobby)
{
	int	slot;

	slot = lbb_get_index(msg);
	if (slot < 0)
		return ;
	ft_memset(&lobby[slot], 0, sizeof(t_player));
}

void	update_player(const char *msg, t_player *lobby)
{
	int	slot;

	slot = lbb_get_index(msg);
	if (slot < 0)
		return ;
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
}

void	host_player(const char *msg, t_player *lobby)
{
	int	slot;

	(void)lobby;
	slot = lbb_get_index(msg);
	if (slot < 0)
		return ;
	lbb_move_player(slot, 0);
}	