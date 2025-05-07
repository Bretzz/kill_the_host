/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_to_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:40:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 22:11:36 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

/* converts the stat in player into an alloc'd msg-string.
RETURNS: the alloc'd msg-string pointer. */
void	*lbb_to_msg(t_player player)
{
	char	*msg;

	msg = (char *)malloc(86 * sizeof(char));
	if (msg == NULL)
		return (NULL);
	ft_memset(msg, 0, 86);
	ft_strlcpy(msg, player.name, ft_strlen(player.name) + 1);
	ft_strlcat(msg, ":", ft_strlen(msg) + 2);
	ft_strlcat(msg, player.ip, ft_strlen(msg) + ft_strlen(player.ip) + 1);
	ft_strlcat(msg, ":", ft_strlen(msg) + 2);
	rebuild_coord(player.pos, &msg[ft_strlen(msg)]);
	ft_strlcat(msg, ":", ft_strlen(msg) + 2);
	rebuild_coord(player.tar, &msg[ft_strlen(msg)]);
	// ft_strlcat(msg, player.pos_tar, ft_strlen(msg) + ft_strlen(player.pos_tar) + 1);
	// if (!player.pos[0] && !player.pos[1] && !player.pos[2])
	// 	ft_strlcat(msg, ":", 86);
	// if (!player.tar[0] && !player.tar[1] && !player.tar[2])
	// 	ft_strlcat(msg, ":", 86);
	return (msg);
}
