/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:35:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/07 22:55:31 by topiana-         ###   ########.fr       */
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
		send_all(mlx, buffer, ft_strlen(buffer));
	}
	else
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}

/* static int	handle_UpDw_press(int keysym, void *arg)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)arg;
	if (keysym == XK_Down || keysym == XK_s || keysym == 125 || keysym == 1)
		mlx->player[*mlx->index].pos.y += 10;
	else if (keysym == XK_Up || keysym == XK_w || keysym == 126 || keysym == 13)
		mlx->player[*mlx->index].pos.y -= 10;
	return (0);
}

static int	handle_LxRx_press(int keysym, void *arg)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)arg;
	if (keysym == XK_Left || keysym == XK_a || keysym == 123 || keysym == 0)
		mlx->player[*mlx->index].pos.x -= 10;
	else if (keysym == XK_Right || keysym == XK_d || keysym == 124 || keysym == 2)
		mlx->player[*mlx->index].pos.x += 10;
	return (0);
} */

int	handle_heypress(int keysym, t_mlx *mlx)
{
	char	buffer[92];
	
	if (keysym == XK_Escape || keysym == 53)
		clean_exit(mlx);
	else if (keysym == XK_KP_Space || keysym == 49 || keysym == 32)
	{
		ft_printf(BLUE"== = = == == =\n");
		print_quick_lobby(mlx->lobby);
		ft_printf(RESET);
		return (0);
	}
	else if (keysym == XK_Down || keysym == XK_s || keysym == 125 || keysym == 1)
		mlx->lobby[*mlx->index].pos[1] += 10;
	else if (keysym == XK_Up || keysym == XK_w || keysym == 126 || keysym == 13)
		mlx->lobby[*mlx->index].pos[1] -= 10;
	else if (keysym == XK_Left || keysym == XK_a || keysym == 123 || keysym == 0)
		mlx->lobby[*mlx->index].pos[0] -= 10;
	else if (keysym == XK_Right || keysym == XK_d || keysym == 124 || keysym == 2)
		mlx->lobby[*mlx->index].pos[0] += 10;
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
	send_all(mlx, buffer, ft_strlen(buffer));
	return (0);
}
