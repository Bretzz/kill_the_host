/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:28:39 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 02:08:00 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

//# include <unistd.h>
# include <ctype.h>
# include <strings.h>
# include <stdlib.h>

/* MSG STRING: "NAME:IP:X_Y_Z:X_Y_Z" */

/* DATA LENGTH */

size_t	msg_ip_length(const char *msg);
size_t	msg_name_length(const char *msg);

/* GET DATA */

char	*msg_get_name(const char *msg, char *buffer);
char	*msg_get_ip(const char *msg, char *buffer);
int		*msg_get_pos(const char *msg, int *pos);
int		*msg_get_tar(const char *msg, int *tar);

#endif