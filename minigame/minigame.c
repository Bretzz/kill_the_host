/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minigame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:13:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/08 00:13:44 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minigame.h"
#include <unistd.h>
#include <signal.h>

int 	clean_exit(t_mlx *mlx);
void	send_all(t_mlx *mlx, const char *msg, size_t msg_size);

int clean_exit(t_mlx *mlx)
{
	char	buffer[92];
	int		socket;
	
	// host and players tell the others to kill them the same way
	buffer_player_action(mlx->lobby[*mlx->index], "kill", buffer);
	
	//game_sender
	sleep(1);
	send_all(mlx, buffer, ft_strlen(buffer));
	if (*mlx->index == HOST)
		ft_memcpy(&socket, mlx->lobby[HOST].online, sizeof(int));
	else
		ft_memcpy(&socket, &mlx->lobby[HOST].online, sizeof(int));
	shutdown(socket, SHUT_RDWR);
	close(socket);	// gets the threads out of the syscall
	sleep(1);
	lbb_kill_player(buffer);	// gets the thread out of the loop
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	print_lobby(mlx->lobby);
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	free(mlx->mlx);
	exit(EXIT_SUCCESS);
}

void	send_all(t_mlx *mlx, const char *msg, size_t msg_size)
{
	int	i;
	int	socket;

	ft_printf(GREEN"sending: %s\n"RESET, msg);
	if (*mlx->index == PLAYER) //sendto host (ClientUDP)
	{
		ft_memcpy(&socket, &mlx->lobby->online, sizeof(int));
		if (send(socket, msg, msg_size, 0) < 0 )
			ft_perror(ERROR"sendto failed"RESET);
		return ;
	}
	i = 1;
	while (i < MAXPLAYERS) //sendto players (ServerUDP)
	{
		// ft_printf("sending to %i\n", i);
		if (lbb_is_alive(mlx->lobby[i]))
		{			
			ft_memcpy(&socket, mlx->lobby[i].online, sizeof(int));
			if (send(socket, msg, msg_size, 0) < 0 )
				ft_perror(ERROR"sendto failed"RESET);
		}
		i++;
	}
}

/* puts all the player info, position and target (with line for shot).
if we got hit by a line (even ours) we exit. */
/* static  */int	handle_player(t_player *lobby, int index, t_mlx *mlx)
{
	static int	lineframes[MAXPLAYERS];
	unsigned int	color;

	if (!lbb_is_alive(lobby[index]))
		return (0);
	if (index == HOST)
		color = 0xFF0000;
	else
		color = 0xFFFFFF;
	my_pixel_put(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	if (lobby[index].tar[0] || lobby[index].tar[1])
	{
		if (lineframes[index] == 10)
		{
			ft_memset(&lobby[index].tar, 0, sizeof(t_point));
			lineframes[index] = 0;
			return (1);
		}
		if (!put_line(mlx,
			lobby[index].pos,
			lobby[index].tar,
			mlx->lobby[*mlx->index].pos,
			color))
			clean_exit(mlx);
		lineframes[index]++;
	}
	return (1);
}

static int	put_board(t_mlx *mlx)
{
	int	i;
	
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);

	i = 0;
	while (i < MAXPLAYERS)
	{
		handle_player(mlx->lobby, i, mlx);
		i++;
	}

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	//ft_printf("ccc\n");
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	//ft_printf("the board is put\n");
	return (1);
}

static int	update_frame(t_mlx *mlx)
{
	static int	frame;

	if (frame % 60 == 0)
		put_board(mlx);
	usleep(1000);
	return (0);
}
/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
static int	juice_the_pc(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win_x = MLX_WIN_X;
	mlx->win_y = MLX_WIN_Y;
	mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_X, MLX_WIN_Y, mlx->lobby[*mlx->index].name);
	if (!mlx->win)
	{
		free(mlx->mlx);
		return (1);
	}
	return (0);
}

int	minigame(int *index, t_player *lobby)
{
	t_mlx	mlx;

	ft_memset(&mlx, 0, sizeof(t_mlx));
	mlx.lobby = lobby;
	mlx.index = index;
	if (juice_the_pc(&mlx))
		return (1);
	
	//ft_printf("pc juiced\n");
	put_board(&mlx);
	//ft_printf("board put\n");

	ft_printf(RED"MLX ADDRESS: %p\n"RESET, &mlx);

	//game mechanics
	mlx_mouse_hook(mlx.win, &handle_mouse, &mlx);
	mlx_key_hook(mlx.win, &handle_heypress, &mlx);
	// mlx_do_key_autorepeaton(mlx.mlx);
	
	//window management
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask, &clean_exit, &mlx);
	mlx_loop_hook(mlx.mlx, &update_frame, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

/* int	main()
{
	t_player player;

	ft_memset(&player, 0, sizeof(t_player));
	if (!minigame(&player))
		return (0);
	return (1);
} */
