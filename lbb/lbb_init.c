/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:07:12 by totommi           #+#    #+#             */
/*   Updated: 2025/05/06 21:09:48 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

void	*lbb_init(void);
void	*lbb_get_ptr(t_player *new_lobby);

/* initialize the lbb_get_ptr's ptr to a
malloc'd t_player array of size MAXPLAYERS.
RETURN it's pointer. */
void	*lbb_init(void)
{
	t_player	*lobby;

	lobby = lbb_get_ptr(NULL);
	free(lobby);
	lobby = (t_player *)malloc(MAXPLAYERS * sizeof(t_player));
	if (lobby == NULL)
		return (NULL);
	ft_memset(lobby, 0, MAXPLAYERS * sizeof(t_player));
	lbb_get_ptr(lobby);
	return (lobby);
}

/* ! ! ! DANGEROUS ! ! ! */
void	*lbb_get_ptr(t_player *new_lobby)
{
	static t_player	*lobby;

	if (new_lobby == NULL)
		return (lobby);
	lobby = new_lobby;
	return (lobby);
}
