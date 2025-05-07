/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:51:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 13:59:48 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_the_host.h"
#include "client.h"

/* -1 error, 0 ok */
int	client_sender(int servfd, void *buffer, size_t size)
{
	ft_printf(YELLOW"sending '%s' to server%s\n", buffer, RESET);
	if (send(servfd, buffer, size, 0) < 0)
	{
		ft_perror(ERROR"send failure"RESET);
		return (-1);
	}
	return (0);
}
