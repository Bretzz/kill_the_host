/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 13:03:49 by topiana-         ###   ########.fr       */
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
