/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:54:25 by ale               #+#    #+#             */
/*   Updated: 2025/05/09 18:35:40 by ade-ross         ###   ########.fr       */
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
	new_line = get_next_line(fd);
	if (!new_line)
	{
		free(str);
		error("no map present in file", NULL, NULL);
	}
	while (new_line)
	{
		temp = ft_strjoin(str, new_line);
		free(new_line);
		free(str);
		if (!temp)
			error("malloc failed in map_line creation", NULL, NULL);
		str = temp;
		new_line = get_next_line(fd);
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

char	**handle_map(char *argv_u, int argc, t_x_and_y *size, t_mlx_data *data)
{
	int		fd;
	char	*map_line;
	char	**map1;

	if (argc < 2)
		error("no arguments dummy", NULL, NULL);
//	check_ber(argv_u);
	fd = open(argv_u, O_RDWR);
	if (fd == -1)
		error("map file not readable or not present", NULL, NULL);
	map_line = create_map_line(fd);
	check_all_characters_are_present(map_line, data);
	map1 = create_map(map_line);
	check_border_is_all_wall(map1, size, map_line);
	//check_is_playable(map_line, size, data, map1); non serve perche non ci sono collectibles e exit
	free(map_line);
	return (map1);
}
