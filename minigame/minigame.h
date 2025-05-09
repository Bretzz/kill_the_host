/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minigame.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:51:09 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 11:58:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIGAME_H
# define MINIGAME_H

//mlx libraries
# include "mlx.h"
// # include "mlx_int.h"	// needed for clean exit
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

// my libs
# include "libft.h"
# include "lbb.h"

// just for colors, ft_perror, print_quick_lobby
# include "kill_the_host.h"

// for msg creation
# include "online.h"

# define MLX_WIN_X 500
# define MLX_WIN_Y 500

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}				t_point;

//player data struct
// typedef struct s_player
// {
// 	char				ip[15];
// 	char				name[10];
// 	// struct sockaddr_in	sockaddr;
// 	int					socket;
// 	t_point				pos;
// 	t_point				target;
// 	int					num;
// 	// pthread_mutex_t		*mutex;
// }				t_player;

//mlx img variables
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

//mlx big struct
typedef struct s_mlx
{
	int				win_x;
	int				win_y;
	int				key_up_dw[2];
	int				key_lx_rx[2];
	void			*mlx;
	void			*win;
	t_img			img;
	t_player		*lobby;
	int				*index;
	int				*socket;
	void			*thread;
}				t_mlx;

int		handle_heypress(int keysym, t_mlx *mlx);
int		handle_mouse(int keysym, int x, int y, t_mlx *mlx);

int		handle_just_press(int keysym, void *arg);
int		handle_just_release(int keysym, void *arg);

void	my_pixel_put(void *my_struct, int x, int y, float z, unsigned int color);
int		put_line(t_mlx *mlx, int *p, int *t, int *my_pos, unsigned int color);
void	put_square(void *my_struct, int x, int y, float z, unsigned int color);

void	send_all(t_mlx *mlx, char *msg, size_t msg_size, char flag);

int 	clean_exit(t_mlx *mlx);

#endif