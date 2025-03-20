/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:44:58 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 12:56:29 by topiana-         ###   ########.fr       */
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
	char	pos_tar[30];
}				t_player;

extern t_player *g_lobby;

/* BASICS */

void	*lbb_init(t_player *lobby);

/* DATA MEASUREMENT */

size_t	lbb_name_length(const char *name);
size_t	lbb_ip_length(const char *ip);

/* READ DATA */

int		lbb_get_index(const char *msg);
int		lbb_next_free_slot(void);
int		lbb_is_alive(t_player player);
size_t	lbb_player_count(void);

/* WRITE DATA */

int		lbb_add_player(const char *msg);
int		lbb_update_player(const char *msg);
void	lbb_kill_player(const char *msg);
void	*lbb_move_player(int src, int dest);
void	lbb_push_up(void);

/* LBB to MSG */

void	*lbb_to_msg(t_player player);

#endif