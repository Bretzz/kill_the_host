/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:45:10 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 21:53:06 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

int		str_skip(const char *s, int count, int c);

/* return the index of the first char after 'count'
instances of 'c' in 's'. */
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
