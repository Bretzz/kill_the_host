/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minigame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:13:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 17:08:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minigame.h"
#include <unistd.h>

void	send_all(t_mlx *mlx, char *msg, size_t msg_size, char flag);

// int clean_exit(t_mlx *mlx)
// {
// 	char	buffer[92];
	
// 	// host and players tell the others to kill them the same way
// 	buffer_player_action(mlx->lobby[*mlx->index], "kill", buffer);
	
// 	//game_sender
// 	send_all(mlx, buffer, ft_strlen(buffer), 0);
// 	// if (*mlx->index == HOST)
// 	// 	ft_memcpy(&socket, mlx->lobby[HOST].online, sizeof(int));
// 	// else
// 	// 	ft_memcpy(&socket, &mlx->lobby[HOST].online, sizeof(int));
// 	shutdown(*mlx->socket, SHUT_RDWR);
// 	close(*mlx->socket);	// gets the threads out of the syscall
// 	sleep(1);
// 	// lbb_kill_player(buffer);	// gets the thread out of the loop
// 	mlx_destroy_window(mlx->mlx, mlx->win);
// 	mlx_destroy_display(mlx->mlx);
// 	print_lobby(mlx->lobby);
// 	// wait the thread
// 	lbb_delete_lobby((lbb_get_ptr(NULL)));
// 	free(mlx->mlx);
// 	exit(EXIT_SUCCESS);
// 	return (0);
// }

void	send_all(t_mlx *mlx, char *msg, size_t size, char flag)
{
	if (flag == -1)
	{
		if (*mlx->index == HOST)
			server_sender(*mlx->socket, msg, NULL, flag);	//destroy mutex
		else
			client_sender(flag, msg, size);					// destroy mutex
	}
	else
	{
		if (*mlx->index == HOST)
			server_sender(*mlx->socket, msg, NULL, 0);
		else
			client_sender(*mlx->socket, msg, size);
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
	put_square(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	//my_pixel_put(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	if (lobby[index].tar[0] || lobby[index].tar[1])
	{
		if (lineframes[index] == 1)
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
		{
			if (*mlx->index == HOST)
			{
				char	buffer[MAXLINE];
				buffer_player_action(mlx->lobby[index], "host", buffer);
				send_all(mlx, buffer, ft_strlen(buffer), 0);
			}
			clean_exit(mlx);
		}
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
	char		moved;
	char		buffer[92];
	
	if (frame++ % 20 == 0)
	{
		moved = 0;
		if (mlx->key_up_dw[0] == 1 && mlx->lobby[*mlx->index].pos[1] -10 > 0 && ++moved)
			mlx->lobby[*mlx->index].pos[1] -= 10;
		if (mlx->key_up_dw[1] == 1 && mlx->lobby[*mlx->index].pos[1] +10 < mlx->win_y && ++moved)
			mlx->lobby[*mlx->index].pos[1] += 10;
		if (mlx->key_lx_rx[0] == 1 && mlx->lobby[*mlx->index].pos[0] -10 > 0 && ++moved)
			mlx->lobby[*mlx->index].pos[0] -= 10;
		if (mlx->key_lx_rx[1] == 1 && mlx->lobby[*mlx->index].pos[0] +10 < mlx->win_x && ++moved)
			mlx->lobby[*mlx->index].pos[0] += 10;
		if (moved != 0)
		{
			buffer_player_action(mlx->lobby[*mlx->index], "update", buffer);
			// ft_printf("send_all(%p, %s, %u)\n", mlx, buffer, ft_strlen(buffer));
			send_all(mlx, buffer, ft_strlen(buffer), 0);
		}
		put_board(mlx);
	}
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

/* Index = PLAYER ? HOST, socket = pointer to socket, thread = pointer to tid */
int	minigame(int *index, int *socket, void *thread)
{
	t_mlx	mlx;

	ft_memset(&mlx, 0, sizeof(t_mlx));
	mlx.lobby = lbb_get_ptr(NULL);
	mlx.index = index;
	mlx.socket = socket;
	mlx.thread = thread;
	if (juice_the_pc(&mlx))
		return (1);
	
	//ft_printf("pc juiced\n");
	put_board(&mlx);
	//ft_printf("board put\n");

	ft_printf(RED"MLX ADDRESS: %p socket %d\n"RESET, &mlx, *mlx.socket);

	//game mechanics
	mlx_mouse_hook(mlx.win, &handle_mouse, &mlx);
	mlx_key_hook(mlx.win, &handle_heypress, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_just_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, &handle_just_release, &mlx);
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
