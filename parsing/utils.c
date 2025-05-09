/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:16 by ale               #+#    #+#             */
/*   Updated: 2025/02/25 21:24:39 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_m(const char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	error(char *s, char **map, char *map_line)
{
	if (map)
		free_map(map);
	if (map_line)
		free(map_line);
	write(2, "Error\n", 6);
	write(2, s, ft_strlen_m(s));
	write(2, "\n", 1);
	exit(1);
}
