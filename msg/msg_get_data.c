/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:39 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 12:57:26 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.h"

char	*msg_get_name(const char *msg, char *buffer);
char	*msg_get_ip(const char *msg, char *buffer);
int		*msg_get_pos(const char *msg, int *pos);
int		*msg_get_tar(const char *msg, int *tar);
char	*msg_get_pos_tar(const char *msg, char *pos_tar);

/* expected a buffer of size >43
Takes a msg-string and a buffer as parameters.
Copies the 'name' value into the buffer and returns it.
RETURNS: the buffer pointer, NULL if buffer is NULL.
NOTE: if msg is NULL and buffer isn't buffer is still bzero'd. */
char	*msg_get_name(const char *msg, char *buffer)
{
	int	name;
	int	i;
	
	if (buffer == NULL)
		return (NULL);
	memset(buffer, 0, 43 * sizeof(char));
	if (msg == NULL)
		return (buffer);
	name = msg_name_length(msg);
	i = 0;
	while(i < name)
	{
		buffer[i] = msg[i];
		i++;
	}
	return (buffer);
}

/* expected a buffer of size >16
Takes a msg-string and a buffer as parameters.
Copies the 'ip' value into the buffer and returns it.
RETURNS: the buffer pointer, NULL if buffer is NULL.
NOTE: if msg is NULL and buffer isn't buffer is still bzero'd. */
char	*msg_get_ip(const char *msg, char *buffer)
{
	int	ip;
	int	i[2];
	
	if (buffer == NULL)
		return (NULL);
	memset(buffer, 0, 16 * sizeof(char));
	if (msg == NULL)
		return (buffer);
	i[0] = msg_name_length(msg) + 1;
	ip = i[0] + msg_ip_length(msg);
	i[1] = 0;
	while(i[0] < ip)
	{
		buffer[i[1]] = msg[i[0]];
		i[0]++;
		i[1]++;
	}
	return (buffer);
}
/* 
#include <stdio.h> */

static int	*msg_atoi(const char *msg, int *dest)
{
	int i;
	
	i = 0;
	dest[0] = atoi(&msg[i]);
	while (msg[i] != '\0' && msg[i] != '_')
		i++;
	dest[1] = atoi(&msg[(++i)]);
	while (msg[i] != '\0' && msg[i] != '_')
		i++;
	dest[2] = atoi(&msg[(++i)]);
	return (dest);
}

/* expected a pos of size 3
Takes a msg-string and an int pointer as parameters.
Assign the vaues writen in msg to pos using atoi(3).
RETURNS: the pos pointer, NULL if pos is NULL.
NOTE: be careful about string without X_Y_Z.
NOTE2: pos is left untouched if 'msg' or 'pos' are NULL. */
int	*msg_get_pos(const char *msg, int *pos)
{
	int	skip;
	int	i;

	if (pos == NULL)
		return (NULL);
	memset(pos, 0, 3 * sizeof(int));
	if (msg == NULL)
		return (pos);
	i = 2;
	skip = 0;
	while (msg[skip] != '\0' && i > 0)
	{
		if (msg[skip] == ':')
			i--;
		skip++;
	}
	if (!isdigit(msg[skip])
		&& msg[skip] != '+'
		&& msg[skip] != '-')
		return (pos);
	pos = msg_atoi(&msg[skip], pos);
	return (pos);
}

/* expected a tar of size 3
Takes a msg-string and an int pointer as parameters.
Assign the vaues writen in msg to tar using atoi(3).
RETURNS: the tar pointer, NULL if tar is NULL. */
int	*msg_get_tar(const char *msg, int *tar)
{
	int	skip;
	int	i;

	if (tar == NULL)
		return (NULL);
	memset(tar, 0, 3 * sizeof(int));
	if (msg == NULL)
		return (tar);
	i = 3;
	skip = 0;
	while (msg[skip] != '\0' && i > 0)
	{
		if (msg[skip] == ':')
			i--;
		skip++;
	}
	if (!isdigit(msg[skip])
		&& msg[skip] != '+'
		&& msg[skip] != '-')
		return (tar);
	tar = msg_atoi(&msg[skip], tar);
	return (tar);
}

/* expected a pos_tar of size 30
Takes a msg-string and an char pointer as parameters.
Assign the vaues writen in msg to pos_tar using strlcpy(3).
RETURNS: the pos_tar pointer, NULL if pos_tar is NULL.
NOTE: copies the end part of the msg-string 'X_Y_Z:X_Y_Z' into 'pos_tar'. */
char	*msg_get_pos_tar(const char *msg, char *pos_tar)
{
	int	skip;
	int	i;

	if (pos_tar == NULL)
		return (NULL);
	memset(pos_tar, 0, 3 * sizeof(int));
	if (msg == NULL)
		return (pos_tar);
	i = 2;
	skip = 0;
	while (msg[skip] != '\0' && i > 0)
	{
		if (msg[skip] == ':')
			i--;
		skip++;
	}
	ft_strlcpy(pos_tar, &msg[skip], strlen(&msg[skip]));
	return (pos_tar);
}
