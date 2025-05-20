/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:48:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/16 18:02:39 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Should this segfault? */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	// if (s == NULL)
	// 	return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
