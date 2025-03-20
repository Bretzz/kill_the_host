/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:07:12 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 02:06:26 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

t_player	*g_lobby = NULL;

void	*lbb_init();

/* Allocates memory for a MAXPLAYERS size lobby.
Assign the pointer returned by malloc(3) to the global variable,
then returns it's value. */
void	*lbb_init()
{
	g_lobby = (t_player *)malloc(MAXPLAYERS * sizeof(t_player));
	if (g_lobby == NULL)
		return (NULL);
	bzero(g_lobby, MAXPLAYERS * sizeof(t_player));
	return (g_lobby);
}

/* ! ! ! DANGEROUS ! ! ! */
void	*lbb_get_ptr()
{
	return (g_lobby);
}
