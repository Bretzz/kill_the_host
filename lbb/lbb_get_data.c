/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:29:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 22:11:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

char	*lbb_get_full_stats(t_player player, void *buffer);

/* converst all the data in the player struct to a msg-string
the string is then copied into buffer and returned the buffer pointer.
If buffer is NULL, returns NULL, otherwise player stats are copied.
EXPECTED: buffer of size >85 */
char	*lbb_get_full_stats(t_player player, void *buffer)
{
	char	*msg;

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, 86);
	msg = lbb_to_msg(player);
	if (msg == NULL)
		return (buffer);
	ft_strlcpy(buffer, msg, 86);
	free(msg);
	return (buffer);
}

/* Expected a buffer of size >(86 * MAXPLAYERS).
lbb_get_full_stats call on the whole lobby, separated by '\n' */
char	*lbb_get_lobby_stats(t_player *lobby, void *buffer)
{
	const size_t	player_count = lbb_player_count();
	char	*buffer_c;
	unsigned int	count;
	unsigned int	i;

	if (buffer == NULL)
		return (buffer);
	ft_memset(buffer, 0, 86 * MAXPLAYERS);
	if (lobby == NULL)
		return (buffer);
	buffer_c = (char *)buffer;
	count = 0;
	i = 0;
	while (i < MAXPLAYERS && count < player_count)
	{
		if (lbb_is_alive(lobby[i]))
		{
			lbb_get_full_stats(lobby[i], &buffer_c[(count * 86) + count]);
			count++;
			if (count < player_count)
				ft_strlcat(buffer_c, "\n", 86 * MAXPLAYERS);
		}
		i++;
	}
	return (buffer);
}
