/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:31:53 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 01:19:36 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
#include "libft.h"

void	print_player(t_player player);
void	print_lobby(t_player *lobby);

void	print_player(t_player player)
{
	char	buffer[86];
	
	if (!lbb_is_alive(player))
		ft_printf("(empty slot)\n");
	else
		ft_printf("%s\n", lbb_get_full_stats(player, buffer));
}

void	print_lobby(t_player *lobby)
{
	int	i;
	
	i = 0;
	while (i < MAXPLAYERS)
	{
		print_player(lobby[i]);
		i++;
	}
}
