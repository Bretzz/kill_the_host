/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:54:25 by ale               #+#    #+#             */
/*   Updated: 2025/05/09 20:28:21 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_ber(char *s)
{
	if (ft_strlen_m
		(s) >= 4)
	{
		if (ft_strncmp(s + (ft_strlen_m(s) - 4), ".ber", 4) == 0)
			return ;
	}
	error("map is not .ber", NULL, NULL);
}

char	*create_map_line(int fd)
{
	char	*str;
	char	*temp;
	char	*new_line;

	str = malloc(1);
	if (!str)
		error("malloc failed", NULL, NULL);
	str[0] = '\0';
	ft_printf("before gnl\n");
	new_line = get_next_line(fd);
	ft_printf("after gnl\n");
	if (!new_line)
	{
		free(str);
		error("no map present in file", NULL, NULL);
	}
	int	i = 0;
	while (new_line && i < 6)
	{
		ft_printf("line\n");
		temp = ft_strjoin(str, new_line);
		free(new_line);
		free(str);
		if (!temp)
			error("malloc failed in map_line creation", NULL, NULL);
		str = temp;
		new_line = get_next_line(fd);
		i++;
	}
	return (str);
}

char	**create_map(char *map_line)
{
	char	**map;
	int		len;
	int		x;

	map = ft_split(map_line, '\n');
	if (!map)
		error("malloc failed in map creation", NULL, map_line);
	len = ft_strlen_m(map[0]);
	x = 1;
	/* while (map[x] != NULL) // levato che mappa debba essere rettangolare
	{
		if (len != ft_strlen_m
			(map[x]))
		{
			error("map is not rectangular", map, map_line);
		}
		len = ft_strlen_m(map[x]);
		x++;
	} */
	return (map);
}

char	**handle_map(char *s)
{
	int		fd;
	char	*map_line;
	char	**map1;

	ft_printf("map handler in\n");
	if (!s)
		error("no map path present", NULL, NULL);
//	check_ber(s);
	fd = open(s, O_RDWR);
	if (fd == -1)
		error("map file not readable or not present", NULL, NULL);
	map_line = create_map_line(fd);
	ft_printf("map line out\n");
	check_all_characters_are_present(map_line);
	ft_printf("check characters out\n");
	map1 = create_map(map_line);
	// check_border_is_all_wall(map1, map_line);
	ft_printf("check borders out\n");
	//check_is_playable(map_line, size, data, map1); non serve perche non ci sono collectibles e exit
	close(fd);
	free(map_line);
	return (map1);
}
