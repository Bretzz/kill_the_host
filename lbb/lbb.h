/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:44:58 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 02:06:42 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LBB_H
# define LBB_H

# ifndef MAXPLAYERS
#  define MAXPLAYERS 10
# endif

# include "msg.h"

typedef struct	s_player
{
	char	name[43];	// max name length: 42
	char	ip[16];		//max ip length: 15
	int		pos[3];
	int		tar[3];
}				t_player;

extern t_player *g_lobby;

/* BASICS */

void	*lbb_init();

/* DATA MEASUREMENT */

size_t	lbb_name_length(const char *name);
size_t	lbb_ip_length(const char *ip);

/* READ DATA */

int		lbb_get_index(const char *msg);
int		lbb_next_free_slot();

/* WRITE DATA */

int	lbb_add_player(const char *msg);
int	lbb_update_player(const char *msg);


#endif