/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_write_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:16:46 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 12:52:36 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

int		lbb_add_player(const char *msg);
int		lbb_update_player(const char *msg);
void	lbb_kill_player(const char *msg);
void	*lbb_move_player(int src, int dest);
void	lbb_push_up(void);

/* takes a msg-string as parameter.
adds the data of the player found (if there's any empty slot in the lobby).
RETURNS: 1 if data was written successfully, 0 if msg is NULL or lobby is full. */
int	lbb_add_player(const char *msg)
{
	int	slot;

	if (!g_lobby || !msg)
		return (0);
	slot = lbb_next_free_slot();
	if (slot < 0)
		return (0);
	msg_get_name(msg, g_lobby[slot].name);
	msg_get_ip(msg, g_lobby[slot].ip);
	msg_get_pos(msg, g_lobby[slot].pos);
	msg_get_tar(msg, g_lobby[slot].tar);
	msg_get_pos_tar(msg, g_lobby[slot].pos_tar);
	return (1);
}

/* takes a msg-string as parameter.
updates the data of the player found.
RETURNS: 1 if data was written successfully, 0 if the player wasn't found */
int	lbb_update_player(const char *msg)
{
	int		index;

	if (!g_lobby || !msg)
		return (0);
	index = lbb_get_index(msg);
	if (index < 0)
		return (0);
	msg_get_pos(msg, g_lobby[index].pos);
	msg_get_tar(msg, g_lobby[index].tar);
	msg_get_pos_tar(msg, g_lobby[index].pos_tar);
	return (1);
}

void	lbb_kill_player(const char *msg)
{
	int	index;

	index = lbb_get_index(msg);
	if (index < 0)
		return ;
	memset(&g_lobby[index], 0, sizeof(t_player));
}

/* moves the player at the index 'src' to the index 'dest'.
After that bzeros the player 'src'.
RETURNS: a ptr to the new player 'src' index (dest), NULL if player is null. */
void	*lbb_move_player(int src, int dest)
{
	if (g_lobby == NULL)
		return (NULL);
	if (src < 0 || src >= MAXPLAYERS)
		return (NULL);
	if (dest < 0 || dest >= MAXPLAYERS)
		return (NULL);
	if (dest == src)
		return (NULL);
	memmove(&g_lobby[dest], &g_lobby[src], sizeof(t_player));
	memset(&g_lobby[src], 0, sizeof(t_player));
	//g_lobby[dest].num = dest;
	return (&g_lobby[dest]);
}

/* compacts to the top all the players left.
ex:
[0]: host
[1]:
[2]: player2
[3]: 
[4]: player4
->
[0]: host
[1]: player2
[2]: player4
[3]:
[4]: */
void	lbb_push_up(void)
{
	int	i[2];
	int	slot;
	
	if (g_lobby == NULL)
		return ;
	i[0] = 0;
	while (i[0] < MAXPLAYERS)
	{
		slot = lbb_next_free_slot();
		if (slot < 0)
			break ;
		i[1] = slot + 1;
		while (i[1] < MAXPLAYERS)
		{
			if (lbb_is_alive(g_lobby[i[1]]))
			{
				lbb_move_player(i[1], slot);
				break ;
			}
			i[1]++;
		}
		i[0]++;
	}
}
