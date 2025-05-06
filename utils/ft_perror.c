/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:23:28 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 23:02:47 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <string.h>

int	ft_perror(const char *string)
{
	ft_printfd(STDERR_FILENO, "%s: %s\n", string, strerror(errno));
	return (errno);
}
