/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:42:19 by totommi           #+#    #+#             */
/*   Updated: 2025/05/08 02:10:10 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "msg.h"
#include "kill_the_host.h"
// #include <sys/wait.h>
#include <pthread.h>

// static void	print_player(t_player player)
// {
// 	char	buffer[86];
	
// 	if (!lbb_is_alive(player))
// 		ft_printf("(empty slot)\n");
// 	else
// 		ft_printf("%s\n", lbb_get_full_stat(player, buffer));
// }

// static void print_lobby(t_player *lobby)
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < MAXPLAYERS)
// 	{
// 		print_player(lobby[i]);
// 		i++;
// 	}
// }

int	main(int argc, char *argv[], char *env[])
{
	const unsigned char	small = 0x7f;
	t_player			*lobby;
	int					index;
	//char		pos_tar[30];
	// char		name[43];
	// char		ip[16];
	// int			pos[3];
	// int			tar[3];
	
	(void)argc; (void)argv; (void)env;
	// if (argc < 2)
	// 	return (1);
	if (lbb_init((void *)&small) == NULL)
		return (1);
	ft_printf("lobby initialized\n");
	lobby = lbb_get_ptr(NULL);
	ft_printf("1\n");
	print_lobby(lobby);
	ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	

	// lbb_add_player("pippo:4.3.2.1:1_2_3");
	// lbb_add_player("donalduck:192.168.1.5:100_200_300");
	// lbb_add_player("pluto:127.0.0.1:9999_9999_9999");
	// // lbb_add_player("michele:255.255.255.255:-a9_+123_543213123");	// crash on mac
	// lbb_add_player(argv[1]);
	// print_lobby(lobby);
	// ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	// lbb_kill_player("donalduck:192.168.1.5");
	// lbb_kill_player("michele:255.255.255.255");
	// print_lobby(lobby);
	// ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	// lbb_move_player(0, 9);
	// print_lobby(lobby);
	// ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	// lbb_push_up();
	// print_lobby(lobby);
	// ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	
	// ft_printf("msg_name_length=%u\n", msg_name_length(argv[1]));
	// ft_printf("msg_get_name: '%s'\n", msg_get_name(argv[1], name));
	// ft_printf("msg_ip_length=%u\n", msg_ip_length(argv[1]));
	// ft_printf("msg_get_ip: '%s'\n", msg_get_ip(argv[1], ip));
	// msg_get_pos(argv[1], pos);
	// ft_printf("msg_get_pos: '%d_%d_%d'\n", pos[0], pos[1], pos[2]);
	// msg_get_tar(argv[1], tar);
	// ft_printf("msg_get_tar: '%d_%d_%d'\n", tar[0], tar[1], tar[2]);
	
	// char	str[] = "michele:255.255.255.255:-a9_+123_543213123";
	// ft_printf("str_skip='%c'\n", str[str_skip(str, 2, ':')]);

	//ft_printf("msg='%s'\n", (char *)lbb_to_msg(lobby[0]));
	// ft_printf("msg_get_pos_tar='%s'\n", msg_get_pos_tar(argv[1], pos_tar));
	// print_lobby(lobby);
	// ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	//ft_printf("name='%s'\nip='%s'\npos=%d_%d_%d\n", lobby[0].name, lobby[0].ip, lobby[0].pos[0], lobby[0].pos[1], lobby[0].pos[2]);
	ft_printf(LOG"THIS THING CRASHES: right now each player has his online stuff in 'server' mode but the message aren't beingn rebound to anyone, so it's useless, he just listens.\nthe client is almost done, we need the send-message part then, thhe ones that qquits cleanly on host's death (also for server), then all good%s\n", RESET);
	pthread_t	listid;
	pthread_t	servtid;

	// #include <signal.h>
	// sigaction(SIGUSR1, NULL, NULL);

	if (!ft_strcmp("host", get_serv_ip(env)))
	{
		listid = server_routine(lobby, env);
		if (listid == 0)
		{
			lbb_delete_lobby((lbb_get_ptr(NULL)));
			return (1);
		}
		usleep(1000);
		index = 0;
		minigame(&index, lobby);
		pthread_join(listid, NULL);
		print_lobby(lobby);
	}
	else
	{
		servtid = client_routine(lobby, env);
		if (servtid == 0)
		{
			lbb_delete_lobby((lbb_get_ptr(NULL)));
			return (1);
		}
		// int servfd;
		// ft_memcpy(&servfd, &lobby->online, sizeof(int));

		// char *line;
		// while ((line = get_next_line(STDIN_FILENO)) != NULL)
		// {
		// 	line[ft_strlen(line) - 1] = '\0';
		// 	client_sender(servfd, line, ft_strlen(line));
		// 	free(line);
		// }
		usleep(1000);
		index = 1;
		minigame(&index, lobby);
		pthread_join(servtid, NULL);
		print_lobby(lobby);
		
	}
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	return (0);
}
