/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:48:24 by totommi           #+#    #+#             */
/*   Updated: 2025/05/09 21:52:10 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

/* MAP CHECKS */

void	check_characters_array(int *characters_arr, char *map_line);
void	check_all_characters_are_present(char *map_line);
void	check_border_is_all_wall(char **map, char *map_line);

int	ft_strlen_m(const char *s);
void	error(char *s, char **map, char *map_line);

#endif