/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:35:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 17:41:21 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minigame.h"

int	handle_heypress(int keysym, t_mlx *mlx);
int	handle_mouse(int keysym, int x, int y, t_mlx *mlx);

int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	char	buffer[92];

	if (keysym == 1) // keysym == 1
	{
		(void)x; (void)y;
		mlx->lobby[*mlx->index].tar[0] = x;
		mlx->lobby[*mlx->index].tar[1] = y;
		ft_printf("PIU-PIU!!!\n");
		//player_specs(mlx->lobby[*mlx->index]);
		buffer_player_action(mlx->lobby[*mlx->index], "update", buffer);
		// ft_printf("send_all(%p, %s, %u)\n", mlx, buffer, ft_strlen(buffer));
		send_all(mlx, buffer, ft_strlen(buffer), 0);
	}
	else
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}

/* static */int	handle_just_press(int keysym, void *arg)
{
	t_mlx	*mlx;
	char	buffer[92];

	mlx = (t_mlx *)arg;
	if (keysym == XK_Escape || keysym == 53)
	{
		if (*mlx->index == HOST)
		{
			buffer_player_action(mlx->lobby[lbb_next_free_slot() - 1], "host", buffer);
			send_all(mlx, buffer, ft_strlen(buffer), 0);
		}
		// ft_printf("buffer is '%s'\n", buffer);
		clean_exit(mlx);
	}
	else if (keysym == XK_KP_Space || keysym == 49 || keysym == 32)
	{
		ft_printf(BLUE"== = = == == =\n");
		ft_printf("status: ");
		if (*mlx->index == HOST)
			ft_printf("HOST");
		else
			ft_printf("PLAYER");
		ft_printf(", socket %d\n", *mlx->socket);
		print_quick_lobby(mlx->lobby);
		ft_printf(RESET);
		return (0);
	}
	if (keysym == XK_Up || keysym == XK_w || keysym == 126 || keysym == 13)
		mlx->key_up_dw[0] = 1;
	else if (keysym == XK_Down || keysym == XK_s || keysym == 125 || keysym == 1)
		mlx->key_up_dw[1] = 1;
	else if (keysym == XK_Left || keysym == XK_a || keysym == 123 || keysym == 0)
		mlx->key_lx_rx[0] = 1;
	else if (keysym == XK_Right || keysym == XK_d || keysym == 124 || keysym == 2)
		mlx->key_lx_rx[1] = 1;
	return (0);
}

/* static */int	handle_just_release(int keysym, void *arg)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)arg;
	if (keysym == XK_Up || keysym == XK_w || keysym == 126 || keysym == 13)
		mlx->key_up_dw[0] = 0;
	else if (keysym == XK_Down || keysym == XK_s || keysym == 125 || keysym == 1)
		mlx->key_up_dw[1] = 0;
	else if (keysym == XK_Left || keysym == XK_a || keysym == 123 || keysym == 0)
		mlx->key_lx_rx[0] = 0;
	else if (keysym == XK_Right || keysym == XK_d || keysym == 124 || keysym == 2)
		mlx->key_lx_rx[1] = 0;
	return (0);
}
/* ! ! ! OUTDATED ! ! ! */
int	handle_heypress(int keysym, t_mlx *mlx)
{
	char	buffer[92];
	
	if (keysym == XK_Escape || keysym == 53)
	{
		buffer_player_action(mlx->lobby[PLAYER], "host", buffer);
		ft_printf("buffer is '%s'\n", buffer);
		send_all(mlx, buffer, ft_strlen(buffer), 0);
		clean_exit(mlx);
	}
	else if (keysym == XK_KP_Space || keysym == 49 || keysym == 32)
	{
		ft_printf(BLUE"== = = == == =\n");
		ft_printf("INDEX: %d, socket %d\n", *mlx->index, *mlx->socket);
		print_quick_lobby(mlx->lobby);
		ft_printf(RESET);
		return (0);
	}
	// else if (keysym == XK_Down || keysym == XK_s || keysym == 125 || keysym == 1)
	// 	mlx->lobby[*mlx->index].pos[1] += 10;
	// else if (keysym == XK_Up || keysym == XK_w || keysym == 126 || keysym == 13)
	// 	mlx->lobby[*mlx->index].pos[1] -= 10;
	// else if (keysym == XK_Left || keysym == XK_a || keysym == 123 || keysym == 0)
	// 	mlx->lobby[*mlx->index].pos[0] -= 10;
	// else if (keysym == XK_Right || keysym == XK_d || keysym == 124 || keysym == 2)
	// 	mlx->lobby[*mlx->index].pos[0] += 10;
	else if (keysym == XK_Delete || keysym == 51)
	{
		clean_exit(mlx);
		//return (0);
	}
	else
		ft_printf("Key Pressed: %i\n", keysym);
	//player_specs(mlx->player[0]); player_specs(mlx->player[1]);
	buffer_player_action(mlx->lobby[*mlx->index], "update", buffer);
	// ft_printf("send_all(%p, %s, %u)\n", mlx, buffer, ft_strlen(buffer));
	send_all(mlx, buffer, ft_strlen(buffer), 0);
	return (0);
}
