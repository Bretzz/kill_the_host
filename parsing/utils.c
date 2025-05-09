/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:16 by ale               #+#    #+#             */
/*   Updated: 2025/05/09 19:40:44 by topiana-         ###   ########.fr       */
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

static void	free_map(char **map)
{
	int	i;

	i = -1;
	if (map)
	{
		while (map[++i])
			free(map[i]);
		free(map);
	}
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
	// exit(1);
}
