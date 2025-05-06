/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:29:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 21:09:41 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

char	*lbb_get_full_stat(t_player player, void *buffer);

/* converst all the data in the player struct to a msg-string
the string is then copied into buffer and returned the buffer pointer.
If buffer is NULL, returns NULL, otherwise player stats are copied.
EXPECTED: buffer of size >85 */
char	*lbb_get_full_stat(t_player player, void *buffer)
{
	char	*msg;

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, 86);
	msg = lbb_to_msg(player);
	if (msg == NULL)
		return (buffer);
	ft_strlcpy(buffer, msg, strlen(msg) + 1);
	free(msg);
	return (buffer);
}
