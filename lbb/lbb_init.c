/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:07:12 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 12:19:40 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

t_player	*g_lobby = NULL;

void	*lbb_init(t_player *lobby);

/* lobby: t_player array of size MAXPLAYERS. 
Sets the whole array to zero, then returns it's pointer.
NOTE: IS THERE A WAY TO CHECK IF 'lobby' ISN'T OF SIZE 'MAXPLAYERS"? */
void	*lbb_init(t_player *lobby)
{
	g_lobby = lobby;
	if (g_lobby == NULL)
		return (NULL);
	memset(g_lobby, 0, MAXPLAYERS * sizeof(t_player));
	return (g_lobby);
}

/* ! ! ! DANGEROUS ! ! ! */
void	*lbb_get_ptr()
{
	return (g_lobby);
}
