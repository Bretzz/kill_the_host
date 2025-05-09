/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:57:18 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/09 18:31:06 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//helper of check_all_characters_are_present
void	check_characters_array(int *characters_arr, char *map_line)
{
	/* if (characters_arr[2] > 1)  //forse questo si poteva lasciare
		error("too many starting points", NULL, map_line); */
/* 	if (characters_arr[4] > 1)
		error("too many exits", NULL, map_line); */
	if (characters_arr[0] == 0)
		error("no walls in map", NULL, map_line);
	if (characters_arr[2] == 0)
		error("no starting point in map", NULL, map_line);
	/* if (characters_arr[3] == 0)
		error("no collectibles in map", NULL, map_line);
	if (characters_arr[4] == 0)
		error("no exit in map", NULL, map_line); */
}

//function checks that all the 5 parts of the map are present
//and that there isn't more tha one starting point
void	check_all_characters_are_present(char *map_line, t_mlx_data *data)
{
	int	characters_arr[5];
	int	i;

	i = -1;
	while (++i < 5)
		characters_arr[i] = 0;
	i = 0;
	while (map_line[i] != '\0')
	{
		if (map_line[i] == '1')
			characters_arr[0] = 1;
		else if (map_line[i] == '0')
			characters_arr[1] = 1;
		else if (map_line[i] == 'P')
			characters_arr[2]++;
		/* else if (map_line[i] == 'C')
			characters_arr[3]++;
		else if (map_line[i] == 'E')
			characters_arr[4]++;*/
		else if (map_line[i] != '\n')
			error("wrong character in map", NULL, map_line);
		i++;
	}
	check_characters_array(characters_arr, map_line);
	data->n_of_collectibles = characters_arr[3];
}

void	check_border_is_all_wall(char **map, t_x_and_y *size, char *map_line)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (y == 0 || map[y + 1] == NULL)
			{
				if (map[y][x] != '1')
					error("map border is not all wall", map, map_line);
			}
			else if (x == 0 || map[y][x + 1] == '\0')
			{
				if (map[y][x] != '1')
					error("map border is not all wall", map, map_line);
			}
			x++;
		}
		y++;
	}
	size->x = x;
	size->y = y;
}
