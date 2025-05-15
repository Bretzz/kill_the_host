/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:31:33 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/15 22:19:28 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minigame.h"

void	my_pixel_put(void *my_struct, int x, int y, float z, unsigned int color);
int		put_line(t_mlx *mlx, int *p, int *t, int *my_pos, int offset, unsigned int color);
void	put_square(void *my_struct, int x, int y, float z, int side, unsigned int color);

void	my_pixel_put(void *my_struct, int x, int y, float z, unsigned int color)
{
	t_mlx	*mlx;
	char	*dst;
	
	(void)z;
	if (!my_struct)
		return ;
	mlx = (t_mlx *)my_struct;
	//ft_printf("putting (%i, %i, %f), with color %x\n", x, y, z, color);
	// If the point is off-screen, do not draw it
	if (x < 0 || y < 0 || /* z > 0 || */ x >= mlx->win_x || y >= mlx->win_y)
		return ;
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_pixel / sizeof(int *)));
	*(unsigned int *)dst = color;
}

void	put_square(void *my_struct, int x, int y, float z, int side, unsigned int color)
{
	int	s_x;
	int	s_y;

	(void)z;
	s_y = y - (side / 2);
	while (s_y < y + (side / 2))
	{
		s_x = x - (side / 2);
		while (s_x < x + (side / 2))
		{
			my_pixel_put(my_struct, s_x, s_y, 0, color);
			s_x++;
		}
		s_y++;
	}
}

/* returns 0 if we got killed. */
int	put_line(t_mlx *mlx, int *p, int *t, int *my_pos, int offset, unsigned int color)
{
	int	proj[2];
	int dx =  abs (t[0] - p[0]), sx = p[0] < t[0] ? 1 : -1;
	int dy = -abs (t[1] - p[1]), sy = p[1] < t[1] ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */
	proj[0] = p[0];
	proj[1] = p[1];

	for (int i = 0;;i++){  /* loop */
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; proj[0] += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; proj[1] += sy; } /* e_xy+e_y < 0 */
		
		my_pixel_put(mlx, proj[0], proj[1], 0, color);
		(void)offset;
		// if (i == offset)
		// {
			// 	put_square(mlx, proj[0], proj[1], 0, 10, color);
			// 	break ;
			// }
		//my stuff (death check)
		if (i > 5 && abs(proj[0] - my_pos[0]) < 5 && abs(proj[1] - my_pos[1]) < 5) return (0);

		if (proj[0] == t[0] && proj[1] == t[1]) break;
	}
	return (1);
}
