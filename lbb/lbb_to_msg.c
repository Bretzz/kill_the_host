/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_to_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:40:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/03/20 12:56:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

/* converts the stat in player into an alloc'd msg-string.
RETURNS: the msg-string pointer. */
void	*lbb_to_msg(t_player player)
{
	char	*msg;

	msg = (char *)malloc(86 * sizeof(char));
	if (msg == NULL)
		return (NULL);
	memset(msg, 0, 86);
	ft_strlcpy(msg, player.name, strlen(player.name) + 1);
	ft_strlcat(msg, ":", strlen(msg) + 2);
	ft_strlcat(msg, player.ip, strlen(msg) + strlen(player.ip) + 1);
	ft_strlcat(msg, ":", strlen(msg) + 2);
	ft_strlcat(msg, player.pos_tar, strlen(msg) + strlen(player.pos_tar) + 1);
	return(msg);
}
