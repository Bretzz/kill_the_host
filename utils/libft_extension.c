/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/16 17:49:53 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_chrnum(const char *s, int c);
int	is_white(char *str);

/* counts how many instances of 'c' in 's'. */
int	ft_chrnum(const char *s, int c)
{
	unsigned int	n;
	size_t			i;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}

size_t	ft_mtxlen(const void **mtx)
{
	size_t	i;

	i = 0;
	while (mtx[i] != NULL)
		i++;
	return (i);
}
