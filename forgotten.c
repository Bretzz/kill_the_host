/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forgotten.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:45:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/15 21:46:47 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




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

/* function that tells me in wich square I am (z coord discarded)*/
static t_point	point_to_quare(int x, int y)
{
	t_point	square;

	square.x = (x / 100);
	square.y = (y / 100);
	return (square);
}

/* GET A RAY? */
/* let's cast the ray in fron */
/* the smallest segment is one "block" */
/* were to draw? front pixed */
/* just check every "block if is full, if it is of what is full?" */
/* each other pixel has different rays (angles) */
/* x and y are the pixel's coordinates */
static unsigned int	cast_ray(t_mlx *mlx, t_local player, int x, int y)
{
	t_point	ray;
	(void)y;
	/* each pixel's angle */
	const float angle_x = player.dir[0] + (player.fov[0] * M_PI / 180) * (1.0f - ((float)x / (mlx->win_x / 2)));
	const float angle_y = player.dir[1] + (player.fov[1] * M_PI / 180) * (1.0f - ((float)y / (mlx->win_y / 2)));

	// if (y) {ft_printf("angle_x of [%d,%d] = %f\n", x, y, angle_x);}
	// if (y) {ft_printf("angle_y of [%d,%d] = %f\n", x, y, angle_y);}
	/* what's the first block my ray intersect? */
	/* where does the ray start? my pos */
	/* ! ! ! MAP COORDINATES ! ! ! */
	ray.x = player.pos[0];
	ray.y = player.pos[1];
	ray.z = 100 / 2;	// arbitrary height of the head

	/* let's do x-intersection first */
	/* if we are in the middle of the square:
		45 < angle_x < -45 north cube, and so on... */
	// y = sin(angle_x) * x
	//t_point original = point_to_quare(ray.x, ray.y);

	t_point square;
	int	incr = 99;
	// ft_printf("incr = %d\n", incr);
	/* map borders */
	while (ray.x < 600 && ray.x > 0
		&& ray.y < 600 && ray.y > 0)
	{
		if (ray.z > 100)
			return (0x0000FF);
		else if (ray.z < 0)
			return (0x00FF00);
		square = point_to_quare(ray.x, ray.y);
		// ft_printf("ray is [%d, %d, %f]\n", (int)ray.x, (int)ray.y, ray.z);
		if (mlx->map[(int)square.y][(int)square.x] == '1'
			&& ray.z < 100)
			return (0xFF0000);
		ray.x -= incr * sin(angle_x);
		ray.y -= cos(angle_x) * incr;
		ray.z += incr * sin(angle_y);
	}
	return (0x000000);
}