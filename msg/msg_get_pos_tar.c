/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_get_pos_tar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:34:46 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 21:18:44 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.h"

char	*msg_get_pos_tar(const char *msg, char *pos_tar);

/* expected buffsize >14 */
static char *rebuild_coord(int *coord, char *buffer)
{
	char	*coord_itoa[3];
	int		i;
	
	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, 15);
	if (coord == NULL)
		return (buffer);
	coord_itoa[0] = ft_itoa(coord[0]);
	coord_itoa[1] = ft_itoa(coord[1]);
	coord_itoa[2] = ft_itoa(coord[2]);
	if (!coord_itoa[0] || !coord_itoa[1] || !coord_itoa[2])
		return (buffer);
	i = 0;
	while (i < 3)
	{
		ft_strlcat(buffer, coord_itoa[i], ft_strlen(buffer) + ft_strlen(coord_itoa[i]) + 1);
		if (i != 2)
			ft_strlcat(buffer, "_", ft_strlen(buffer) + 2);
		i++;
	}
	free(coord_itoa[0]); free(coord_itoa[1]); free(coord_itoa[2]);
	return (buffer);
}

/* expected a buffer of size >30
Takes a msg-string and an char pointer as parameters.
Assign the vaues writen in msg to pos_tar using strlcpy(3).
RETURNS: the pos_tar pointer, NULL if pos_tar is NULL.
NOTE: copies the end part of the msg-string 'X_Y_Z:X_Y_Z' into 'pos_tar'. */
char	*msg_get_pos_tar(const char *msg, char *buffer)
{
	char	coord[15];
	int		pos[3];
	int		tar[3];

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, 30 * sizeof(char));
	if (msg == NULL)
		return (buffer);
	if (!has_pos(msg))
		return (buffer);
	msg_get_pos(msg, pos);
	ft_strlcpy(buffer, rebuild_coord(pos, coord), 16);
	if (!has_tar(msg))
		return (buffer);
	ft_strlcat(buffer, ":", ft_strlen(buffer) + 2);
	msg_get_tar(msg, tar);
	ft_strlcat(buffer, rebuild_coord(pos, coord), ft_strlen(buffer) + ft_strlen(coord) + 1);
	return (buffer);
}
