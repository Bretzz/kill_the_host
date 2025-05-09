/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minigame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:13:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 21:08:16 by topiana-         ###   ########.fr       */
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
	// put_square(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], 10, color);
	//my_pixel_put(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	if (lobby[index].tar[0] || lobby[index].tar[1])
	{
		if (lineframes[index] == 12)
		{
			ft_memset(&lobby[index].tar, 0, sizeof(t_point));
			lineframes[index] = 0;
			return (1);
		}
		if (!put_line(mlx,
			lobby[index].pos,
			lobby[index].tar,
			mlx->lobby[*mlx->index].pos,
			lineframes[index] * (sqrt(pow(lobby[index].pos[0] - lobby[index].tar[0], 2)
				+ pow(lobby[index].pos[1] - lobby[index].tar[1], 2))) / 10,
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

int	my_dist(const int *a, const int *b)
{
	return (sqrt((a[0] - b[0]) * (a[0] - b[0]))
	+ (a[1] - b[1]) * (a[1] - b[1]));
}



// x = 100, pos = [100, 400] (world is just on the ground)
// int	world_to_screen(t_mlx *mlx, int *buffer, int *coord, int *pos)
// {
// 	// max = win_y / 2;
// 	// min = win_y
// 	// int	screen;

// 	// screen = mlx->win_y / (1.0f + 1.0f / (my_dist()));
// 	return (0);
// }

// int	screen_to_world(int coord, int *pos)
// {
	
// }

// wall coordinates are the bot left angle (top vew, nord up)
// top line = win_y - 400, bot line == win_y - 100 (win_y = 500)
// example: x = 100, y = 200
/* 
1 1 1 1 1
1 0 0 0 1
1 1 0 0 1
1 0 0 0 1
1 P 0 0 1
1 1 1 1 1
*/
int put_south_wall(t_mlx *mlx, int x, int y, float z, unsigned int color)
{
	const int	*my_pos = mlx->lobby[*mlx->index].pos;
	const int	wall_centre[2] = { x + (100 / 2), y - (100 / 2) };
	size_t		side;
	// int			top_line;
	// int			bot_line;
	// int			left_line;
	int			surface;

	// dist == 0, side = win_y / 2
	// dist == 100, side = 
	// top_line == 0 -> dist me-wall == 0
	// top_line = my_dist(my_pos, wall_centre);
	// bot_line = mlx->win_y - top_line;
	// left_line = my_dist(my_pos, wall_pos);
	surface = my_dist(my_pos, wall_centre) - (100 / 2);	// distance from the surface wll if we align
	side = mlx->win_y - surface;
	put_square(mlx, x + (side / 2) + z, y + (side / 2) + z, z, side, color);	// screen coordinates
	return (0);
}

/* null terminated array of null terminated strings. */
/* map coord -> real coord = map coord * 100)*/
static int	put_map(t_mlx *mlx, char **map)
{
	unsigned int	i;
	size_t			j;

	if (map == NULL)
		return (1);
	i = 0;
	while (map[i] != NULL)
	{
		// ft_printf("y = %d\n", i);
		j = 0;
		while (map[i][j] != '\0')
		{
			// ft_printf("x = %d\n", j);
			if (map[i][j] == '1')
			{
				int	wall_coord[2] = { j * 100, i * 100 };
				int	slide = my_dist(wall_coord, mlx->lobby[*mlx->index].pos) / 10;// sqrt(abs(mlx->lobby[*mlx->index].pos[1] - wall_coord[1])) * abs(mlx->lobby[*mlx->index].pos[0] - wall_coord[0]);
				if (wall_coord[0] < mlx->lobby[*mlx->index].pos[0])
					wall_coord[0] -= slide;
				if (wall_coord[0] > mlx->lobby[*mlx->index].pos[0])
					wall_coord[0] += slide;
				// if ((abs(mlx->lobby[*mlx->index].pos[0] - wall_coord[0]) < 100))
				if (wall_coord[1] < mlx->lobby[*mlx->index].pos[1])
					put_square(mlx, wall_coord[0], mlx->win_y / 2, 0, mlx->win_y - (abs(mlx->lobby[*mlx->index].pos[1] - wall_coord[1])), 0xf80f0c);
				// future put wall
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	put_board(t_mlx *mlx)
{
	int	i;
	
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);

	put_map(mlx, mlx->map);

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
		mlx_mouse_get_pos(mlx->mlx, mlx->win, &mlx->mouse[0], &mlx->mouse[1]);
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
	ft_printf("bvefore map\n");
	mlx.map = handle_map("parsing/maps/square.ber");
	if (mlx.map == NULL)
		return (1);
	ft_printf("HOT MAP\n");
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
