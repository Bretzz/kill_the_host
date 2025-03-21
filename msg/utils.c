/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:45:10 by topiana-          #+#    #+#             */
/*   Updated: 2025/03/21 12:43:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		str_skip(const char *s, int count, int c);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			d_len;
	size_t			s_len;
	unsigned int	d;
	unsigned int	s;

	s_len = strlen(src);
	d_len = strlen(dst);
	if (size <= d_len)
		return (size + s_len);
	d = d_len;
	s = 0;
	while (src[s] && d + 1 < size)
	{
		dst[d] = src[s];
		d++;
		s++;
	}
	dst[d] = '\0';
	return (s_len + d_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	len;
	unsigned int	i;

	len = strlen(src);
	if (size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

int	str_skip(const char *s, int count, int c)
{
	int skip;
	
	skip = 0;
	while (s[skip] != '\0' && count > 0)
	{
		if (s[skip] == c)
			count--;
		skip++;
	}
	return (skip);
}
