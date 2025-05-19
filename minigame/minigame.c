/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minigame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:13:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 15:32:46 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minigame.h"
#include <unistd.h>

void	put_centre_line(t_mlx *mlx, int x, float len, unsigned int color);

size_t	priv_mtxlen(const void **mtx)
{
	size_t	i;

	i = 0;
	while (mtx[i] != NULL)
		i++;
	return (i);
}

// Normalize the angle to stay within the range [0, 2*PI)
float normalize_angle(float angle)
{
	if (angle < -M_PI)
		return (M_PI - (-angle - M_PI));
	else if (angle > M_PI)
		return (-M_PI + (angle - M_PI));
	return (angle);
}


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


int	put_player(t_mlx *mlx, int *my_pos, int *his_pos, unsigned int color)
{
	(void)mlx; (void)my_pos; (void)his_pos; (void)color;
	const float delta_angle = (mlx->player.fov[0] * M_PI / 180) / mlx->win_x;	// 0 = left, pi/2 = up
	const float angle = normalize_angle(atan2((my_pos[1] - his_pos[1]), (my_pos[0] - his_pos[0])));
	const float	my_dist = sqrt(pow(his_pos[0] - my_pos[0], 2) + pow(his_pos[1] - my_pos[1], 2));
	const float	dir = mlx->player.dir[0] * M_PI / 180;
	// mlx->player.fov[1] = 1;
	const float	ray	= cast_ray(mlx, my_pos, angle);
	// mlx->player.fov[1] = 0;

	(void)delta_angle;
	// ft_printf("player dist = %d\n", my_dist);
	// visibility check
	if (angle < dir - mlx->player.fov[0] * M_PI / 90
		|| angle > dir + mlx->player.fov[0] * M_PI / 90)
		return (1);
	if (ray > 0 && ray < my_dist)
		return (1);
	// visibility check
	// put_square(mlx, mlx->win_x / 2, mlx->win_y / 2, 0, 10, 0xed80e9);
	
	// mlx->win_x = player.fov
	int centre = mlx->win_x / 2 + (angle - dir) / delta_angle;
	put_centre_line(mlx, centre - 2, my_dist, color);
	put_centre_line(mlx, centre - 1, my_dist, color);
	put_centre_line(mlx, centre, my_dist, color);
	put_centre_line(mlx, centre + 1, my_dist, color);
	put_centre_line(mlx, centre + 2, my_dist, color);
	return (0);
}

/* 0 it killed us, 1 it didn't */
int	shoot_laser(t_mlx *mlx, int *pos, float dir, int *my_pos)
{
	const float delta_angle = (mlx->player.fov[0] * M_PI / 180) / mlx->win_x;	// 0 = left, pi/2 = up
	const float kill_angle = normalize_angle(atan2((pos[1] - my_pos[1]), (pos[0] - my_pos[0])));
	const float	my_dist = sqrt(pow(pos[0] - my_pos[0], 2) + pow(pos[1] - my_pos[1], 2));
	if (dir < kill_angle - 10 * delta_angle
		|| dir > kill_angle + 10 * delta_angle)
	{
		ft_printf("DIRECTION OUT\n");
		return (1);
	}
	// mlx->player.fov[1] = 1;
	const int	ray	= cast_ray(mlx, pos, dir);
	// mlx->player.fov[1] = 0;
	ft_printf("my dist %d, ray %d\n", my_dist, ray);
	if (ray > 0 && ray < my_dist)
	{
		ft_printf("OBSTACLE OUT\n");
		return (1);
	}
	return (0);
}

/* puts all the player info, position and target (with line for shot).
if we got hit by a line (even ours) we exit. */
/* static  */int	handle_player(t_player *lobby, int index, t_mlx *mlx)
{
	// static int	lineframes[MAXPLAYERS];
	unsigned int	color;

	if (!lbb_is_alive(lobby[index]))
		return (0);
	if (index == HOST)
		color = 0x4F2B4E;
	else
		color = 0xed80e9;
	if (index != *mlx->index)
		put_player(mlx, mlx->player.pos, mlx->lobby[index].pos, color);
	// put_square(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], 10, color);
	// my_pixel_put(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	if (index != *mlx->index && lobby[index].tar[0])
	{
		if (shoot_laser(mlx, lobby[index].pos, lobby[index].tar[0] * M_PI / 180, mlx->player.pos) == 0)
		{
			if (*mlx->index == HOST)
			{
				char	buffer[MAXLINE];
				buffer_player_action(mlx->lobby[index], "host", buffer);
				send_all(mlx, buffer, ft_strlen(buffer), 0);
			}
			clean_exit(mlx);
		}
	}
	ft_memset(lobby[index].tar, 0, 3 * sizeof(int));
	// if (lobby[index].tar[0] || lobby[index].tar[1])
	// {
	// 	if (lineframes[index] == 1)
	// 	{
	// 		ft_memset(&lobby[index].tar, 0, sizeof(t_point));
	// 		lineframes[index] = 0;
	// 		return (1);
	// 	}
	// 	if (!put_line(mlx,
	// 		lobby[index].pos,
	// 		lobby[index].tar,
	// 		mlx->lobby[*mlx->index].pos,
	// 		0/* lineframes[index] * (sqrt(pow(lobby[index].pos[0] - lobby[index].tar[0], 2)
	// 			+ pow(lobby[index].pos[1] - lobby[index].tar[1], 2))) / 10 */,
	// 		color))
	// 	{
	// 		if (*mlx->index == HOST)
	// 		{
	// 			char	buffer[MAXLINE];
	// 			buffer_player_action(mlx->lobby[index], "host", buffer);
	// 			send_all(mlx, buffer, ft_strlen(buffer), 0);
	// 		}
	// 		clean_exit(mlx);
	// 	}
	// 	lineframes[index]++;
	// }
	return (1);
}

int	my_dist(const int *a, const int *b)
{
	return (sqrt((a[0] - b[0]) * (a[0] - b[0]))
	+ (a[1] - b[1]) * (a[1] - b[1]));
}


/* returns the length of the ray (0 if out of borders?) */
float	cast_ray(t_mlx *mlx, int *pos, float angle)
{
	// const float angle = atan2((pos[1] - tar[1]), (pos[0] - tar[0]));
	int	incr[2];
	int	dir[2];
	int	ray[2];

	ft_memcpy(ray, pos, 2 * sizeof(int));
	dir[0] = fabsf(angle) > M_PI / 2 ? 1 : -1;
	dir[1] = angle > 0 ? -1 : 1;

	// first increment
	incr[0] = dir[0] > 0 ? (ray[0] + 100) / 100 : ray[0] / 100;
	incr[1] = dir[1] > 0 ? (ray[1] + 100) / 100 : ray[1] / 100;
	incr[0] = abs(ray[0] - (incr[0] * 100));
	incr[1] = abs(ray[1] - (incr[1] * 100));

	// ft_printf("angle = %f\ndir[%d,%d]\nincr[%d, %d]\n", angle, dir[0], dir[1], incr[0], incr[1]);
	while (mlx->map[ray[1] / 100][ray[0] / 100] != '1')
	{
		// ft_printf("incr[%d,%d]\n", incr[0], incr[1]);
		if ((/* pos[0] +  */incr[0]) / fabsf(cosf(angle))
			< (/* pos[1] +  */incr[1]) / fabsf(sinf(angle)))
		{
			// ft_printf("X\n");
			// move trough x
			ray[0] = pos[0] + incr[0] * dir[0];
			ray[1] = pos[1] + incr[0] / fabsf(cosf(angle)) * fabsf(sinf(angle)) * dir[1];
			// checks for collisions
			if (dir[0] < 0 && (ray[0] / 100) > 0 && mlx->map[ray[1] / 100][(ray[0] / 100) - 1] == '1')
				break ;
			if (dir[0] > 0 && (ray[0] / 100) < mlx->map_dim[0] && mlx->map[ray[1] / 100][(ray[0] / 100)] == '1')
				break ;
			// modify incr[0]
			incr[0] += 100;
		}
		else
		{
			// ft_printf("Y\n");
			// move trough y
			ray[0] = pos[0] + incr[1] / fabsf(sinf(angle)) * fabsf(cosf(angle)) * dir[0];
			ray[1] = pos[1] + incr[1] * dir[1];
			// checks for collisions
			if (dir[1] < 0 && (ray[1] / 100) > 0 && mlx->map[(ray[1] / 100) - 1][ray[0] / 100] == '1')
				break ;
			if (dir[1] > 0 && (ray[1] / 100) < mlx->map_dim[1] && mlx->map[ray[1] / 100][(ray[0] / 100)] == '1')
				break ;
			// modify incr[1]
			incr[1] += 100;
		}
		// ft_printf("RAY: [%d, %d]\n", ray[0], ray[1]);
		if (ray[0] < 0 || ray[0] >= mlx->map_dim[0] * 100
			|| ray[1] < 0 || ray[1] >= mlx->map_dim[1] * 100)
			return (-1);	//flag it big
	}
	//put_line(mlx, pos, ray, pos, 0, 0xf0f0f0);

	// if (angle == mlx->player.dir[0])
	// 	put_square(mlx, ray[0], ray[1], 0, 30, 0x0000ff);
	// else
	if (mlx->player.fov[1] != 0)
		put_square(mlx, ray[0], ray[1], 0, 10, 0x00ff00);
	
	// ft_printf("%d intersection: [%d, %d]\n", i, ray[0], ray[1]);
	return (sqrt(pow(ray[0] - pos[0], 2) + pow(ray[1] - pos[1], 2)));
}

/* null terminated array of null terminated strings. */
/* map coord -> real coord = map coord * 100)*/
/* static  */void	put_map(t_mlx *mlx, char **map)
{
	unsigned int	i;
	size_t			j;

	if (map == NULL)
		return ;
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
				int	wall_coord[2] = { (j * 100) + 50 , (i * 100) + 50 };
				// if ((abs(mlx->lobby[*mlx->index].pos[0] - wall_coord[0]) < 100))
				put_square(mlx, wall_coord[0], wall_coord[1], 0, 100, 0xf80f0c);
				// future put wall
			}
			j++;
		}
		i++;
	}
}

/* static  */void put_grid(t_mlx *mlx)
{
	int	pos[2];
	int	tar[2];

	ft_bzero(pos, 2 * sizeof(int));
	while (pos[0] < mlx->win_x)
	{
		tar[0] = pos[0];
		tar[1] = mlx->win_x;
		put_line(mlx, pos, tar, pos, 0, 0xFFFFFF);
		pos[0] += 100;
	}
	ft_bzero(pos, 2 * sizeof(int));
	while (pos[1] < mlx->win_x)
	{
		tar[1] = pos[1];
		tar[0] = mlx->win_y;
		put_line(mlx, pos, tar, pos, 0, 0xFFFFFF);
		pos[1] += 100;
	}
}


#include <stdio.h>

// mlx->win_y * e ^ -x
void	put_centre_line(t_mlx *mlx, int x, float len, unsigned int color)
{
	int	heigth;
	int	y;
	const float	dir = mlx->player.dir[1] * M_PI / 180;

	if (len < 0)
		return ;
	if (len == 0)
		heigth = mlx->win_y / 2;
	else
		heigth = (mlx->map_dim[0] * (1.0f + (float)mlx->map_dim[0] / mlx->map_dim[1]) * mlx->win_y) / len;	// dim 0?
	// if (heigth > mlx->win_y / 2)
	// 	heigth = mlx->win_y / 2;
	y = 0;
	while (y < heigth)
	{
		my_pixel_put(mlx, x, sin(dir) * (mlx->win_y) + (mlx->win_y / 2) + y, 0, color);
		my_pixel_put(mlx, x, sin(dir) * (mlx->win_y) + (mlx->win_y / 2) - y, 0, color);
		y++;
	}
}

int	put_sky_floor(t_mlx *mlx)
{
	const float	dir = mlx->player.dir[1] * M_PI / 180;
	int	pixel[2];

	pixel[1] = 0;
	while (pixel[1] < mlx->win_y)
	{
		pixel[0] = 0;
		while (pixel[0] < mlx->win_x)
		{
			if (pixel[1] < sin(dir) * (mlx->win_y) + mlx->win_y / 2)
				my_pixel_put(mlx, pixel[0], pixel[1], 0, 0xadd8e6);
			else
				my_pixel_put(mlx, pixel[0], pixel[1], 0, 0xffffc5);
			pixel[0]++;
		}
		pixel[1]++;
	}
	return (0);
}

int	put_crosshair(t_mlx *mlx)
{
	int	i;

	i = -10;
	while (i < 11)
	{
		my_pixel_put(mlx, mlx->win_x / 2 + i, mlx->win_y / 2, 0, 0xffffff);
		my_pixel_put(mlx, mlx->win_x / 2, mlx->win_y / 2 + i, 0, 0xffffff);
		i++;
	}
	return (0);
}

int	put_fp_view(t_mlx *mlx)
{
	const float delta_angle = (mlx->player.fov[0] * M_PI / 180) / mlx->win_x;	// 0 = left, pi/2 = up
	const float	dir = normalize_angle(mlx->player.dir[0] * M_PI / 180);
	float		len;
	int			i;

	// /* ft_ */printf("DIR %f\n", mlx->player.dir[0]);

	i = -mlx->win_x / 2;
	while (i <= mlx->win_x / 2)
	{
		// mlx->player.fov[1] = 1;
		len = cast_ray(mlx, mlx->player.pos, normalize_angle(dir + i * delta_angle));
		// mlx->player.fov[1] = 0;
		if (len > 0)
			len = len * cosf(i * delta_angle);
		// /* ft_ */printf("casting pixel %d, wit angle %f, got len %f\n", i, dir + i * delta_angle, len);
		put_centre_line(mlx, i + mlx->win_x / 2, len, 0xff0000);
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

	// put_map(mlx, mlx->map);
	// put_grid(mlx);
	put_sky_floor(mlx);
	put_fp_view(mlx);
	put_crosshair(mlx);

	// put_centre_line(mlx, mlx->win_x / 2, 0);

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

int	move_player(t_mlx *mlx)
{
	const int	move_speed = 5;  // Speed of movement
	const float dir = mlx->player.dir[0] * M_PI / 180;
	int			new_pos[2];
	int			moved[2];

	ft_memmove(new_pos, mlx->player.pos, 2 * sizeof(int));
	ft_bzero(moved, 2 * sizeof(int));
	if (mlx->key_up_dw[1] == 1) {
		// Calculate the new X and Y positions using the player's direction
		new_pos[0] += cosf(dir) * move_speed;
		new_pos[1] += sinf(dir) * move_speed;
		++moved[0];
	}
	
	// Move backward (decrease position in direction opposite to the player's facing)
	if (mlx->key_up_dw[0] == 1) {
		new_pos[0] -= cosf(dir) * move_speed;
		new_pos[1] -= sinf(dir) * move_speed;
		++moved[0];
	}
	
	// Move left (rotate 90 degrees counterclockwise and move forward)
	if (mlx->key_lx_rx[1] == 1) {
		float left_angle = dir - M_PI_2;  // 90 degrees counterclockwise
		new_pos[0] += cosf(left_angle) * move_speed;
		new_pos[1] += sinf(left_angle) * move_speed;
		++moved[0];
	}
	
	// Move right (rotate 90 degrees clockwise and move forward)
	if (mlx->key_lx_rx[0] == 1) {
		float right_angle = dir + M_PI_2;  // 90 degrees clockwise
		new_pos[0] += cosf(right_angle) * move_speed;
		new_pos[1] += sinf(right_angle) * move_speed;
		++moved[0];
	}

	// if (dir[0] < 0 && (ray[0] / 100) > 0 && mlx->map[ray[1] / 100][(ray[0] / 100) - 1] == '1')
	// 	break ;
	// if (dir[0] > 0 && (ray[0] / 100) < mlx->map_dim[0] && mlx->map[ray[1] / 100][(ray[0] / 100)] == '1')
	// 	break ;

	if (moved[0] && (new_pos[0] / 100) < mlx->map_dim[0] && new_pos[0] > 0
		&& mlx->map[mlx->player.pos[1] / 100][(new_pos[0] / 100)] != '1' && ++moved[1])
		mlx->player.pos[0] = new_pos[0];

	if (moved[0] && (new_pos[1] / 100) < mlx->map_dim[1] && new_pos[1] > 0
		&& mlx->map[(new_pos[1] / 100)][mlx->player.pos[0] / 100] != '1' && ++moved[1])
		mlx->player.pos[1] = new_pos[1];
	return (moved[1]);
}

int	move_mouse(t_mlx *mlx)
{
	// const float delta_angle = (mlx->player.fov[0] * M_PI / 180) / mlx->win_x;
	if (mlx->on_window == 0)
		return (1);
	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mlx->mouse[0], &mlx->mouse[1]);
	if (mlx->mouse[0] != mlx->win_x / 2)
	{
		mlx->player.dir[0] += (mlx->mouse[0] - (mlx->win_x / 2));
		mlx->player.dir[0] = mlx->player.dir[0] % 360;
		// if (mlx->player.dir[0] < -M_PI)
		// 	mlx->player.dir[0] = M_PI - (-mlx->player.dir[0] - M_PI);
		// else if (mlx->player.dir[0] > M_PI)
		// 	mlx->player.dir[0] = -M_PI + (mlx->player.dir[0] - M_PI);
		// mlx->player.dir[0] = normalize_angle(mlx->player.dir[0]);
		// printf("dir0: %f\n", mlx->player.dir[0]);
	}
	if (mlx->mouse[1] != mlx->win_y / 2)
	{
		mlx->player.dir[1] += ((mlx->win_y / 2) - mlx->mouse[1]) / 2;
		mlx->player.dir[1] = mlx->player.dir[1] % 360;
		// if (mlx->player.dir[0] < -M_PI)
		// 	mlx->player.dir[0] = M_PI - (-mlx->player.dir[0] - M_PI);
		// else if (mlx->player.dir[0] > M_PI)
		// 	mlx->player.dir[0] = -M_PI + (mlx->player.dir[0] - M_PI);
		// printf("dir1: %f\n", mlx->player.dir[1]);
	}
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->win_x / 2, mlx->win_y / 2);
	return (0);
}


static int	update_frame(t_mlx *mlx)
{
	// const float delta_angle = (mlx->player.fov[0] * M_PI / 180) / mlx->win_x;
	static int	frame;
	// int			mouse[2];
	// char		moved;
	char		buffer[92];
	
	if (frame++ % 1 == 0)
	{
		move_mouse(mlx);
		if (move_player(mlx) != 0)
		{
			buffer_player_action(mlx->lobby[*mlx->index], "update", buffer);
			// ft_printf("send_all(%p, %s, %u)\n", mlx, buffer, ft_strlen(buffer));
			send_all(mlx, buffer, ft_strlen(buffer), 0);
		}
		mlx->player.pos = mlx->lobby[*mlx->index].pos;
		mlx->player.tar = mlx->lobby[*mlx->index].tar;
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

int	data_init(t_mlx *mlx, int *index, int *socket, void *thread)
{
	ft_memset(mlx, 0, sizeof(t_mlx));
	mlx->lobby = lbb_get_ptr(NULL);
	mlx->index = index;
	if (juice_the_pc(mlx))
		return (1);
	mlx->socket = socket;
	mlx->thread = thread;
	mlx->player.pos = mlx->lobby[*mlx->index].pos;
	mlx->player.tar = mlx->lobby[*mlx->index].tar;
	mlx->player.pos[0] = 200;
	mlx->player.pos[1] = 200;
	mlx->player.fov[0] = 90;
	mlx->player.fov[1] = 0;
	mlx->player.dir[0] = 0;
	mlx->player.dir[1] = 0;
	ft_printf("bvefore map\n");
	mlx->map = handle_map("parsing/maps/square.ber");
	if (mlx->map == NULL)
		return (1);
	mlx->map_dim[0] = ft_strlen(mlx->map[0]);
	mlx->map_dim[1] = ft_mtxlen((const void **)mlx->map);
	return (0);	
}

/* Index = PLAYER ? HOST, socket = pointer to socket, thread = pointer to tid */
int	minigame(int *index, int *socket, void *thread)
{
	t_mlx	mlx;

	if (data_init(&mlx, index, socket, thread) != 0)
		return (1);

	put_board(&mlx);

	ft_printf(LOG"bouncing up-dow view because of change of dir from radiants to degrees\nlook at put_centre_line()%s\n", RESET);
	ft_printf(RED"MLX ADDRESS: %p socket %d\n"RESET, &mlx, *mlx.socket);

	//game mechanics
	mlx_mouse_hook(mlx.win, &handle_mouse, &mlx);
	// mlx_key_hook(mlx.win, &handle_heypress, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_just_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, &handle_just_release, &mlx);
	
	mlx_hook(mlx.win, EnterNotify, (1L << 4), &enter_notify_handler, &mlx);
	mlx_hook(mlx.win, LeaveNotify, (1L << 5), &leave_notify_handler, &mlx);


	// mlx_do_key_autorepeaton(mlx.mlx);
	mlx_mouse_hide(mlx.mlx, mlx.win);

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
