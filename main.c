/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:42:19 by totommi           #+#    #+#             */
/*   Updated: 2025/03/20 02:17:43 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "msg.h"
#include "lbb.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_player	*lobby;
	char		name[43];
	char		ip[16];
	int			pos[3];
	int			tar[3];
	
	if (argc < 2)
		return (1);
	lbb_init();
	lobby = lbb_add_player("pippohasareallylongname:255.255.255.255:1_1_1:2_2_2");
	/* printf("msg_name_length=%zu\n", msg_name_length(argv[1]));
	printf("msg_get_name: '%s'\n", msg_get_name(argv[1], name));
	printf("msg_ip_length=%zu\n", msg_ip_length(argv[1]));
	printf("msg_get_ip: '%s'\n", msg_get_ip(argv[1], ip));
	msg_get_pos(argv[1], pos);
	printf("msg_get_pos: '%d_%d_%d'\n", pos[0], pos[1], pos[2]);
	msg_get_tar(argv[1], tar);
	printf("msg_get_tar: '%d_%d_%d'\n", tar[0], tar[1], tar[2]); */
	lbb_update_player(argv[1]);
	printff("name='%s'\nip='%s'\npos=%d_%d_%d\ntar=%d_%d_%d\n", )
	return (0);
}
