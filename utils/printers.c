/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:31:53 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 16:27:35 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
#include "libft.h"

void	print_player(t_player player);
void	print_lobby(t_player *lobby);
void	print_quick_lobby(t_player *lobby);

void	print_player(t_player player)
{
	const void	*small = lbb_kill_player(NULL);
	char		buffer[86];
	
	if (!lbb_is_alive(player))
		ft_printf("(empty slot) %p\n", player.online);
	else
	{
		// ft_printf("%p > %p? good\n", player.online, small);
		ft_printf("%s ", lbb_get_full_stats(player, buffer));
		if (player.online >= small)
			ft_printf("online: %p", player.online)/* , ((int *)player.online + 1) */;
		ft_printf("\n");
	}
}

void	print_quick_lobby(t_player *lobby)
{
	char	buffer[86];
	int		i;
	
	i = 0;
	while (i < MAXPLAYERS)
	{
		if(lbb_is_alive(lobby[i]))
			ft_printf("%s\n", lbb_get_full_stats(lobby[i], buffer));
		i++;
	}
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
