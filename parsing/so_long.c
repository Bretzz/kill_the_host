/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:42:03 by ale               #+#    #+#             */
/*   Updated: 2025/05/09 19:15:56 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* void	*load_one(t_mlx_data *data, char *s)
{
	int		im_w;
	int		im_h;
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx, s, &im_w, &im_h);
	return (img);
}

void	load_images(t_mlx_data *data)
{
	data->wall = load_one(data, "./images/wall.xpm");
	data->floor = load_one(data, "./images/backgr.xpm");
	data->player = load_one(data, "./images/player.xpm");
	data->ice_cr = load_one(data, "./images/ice_cr.xpm");
	data->exit = load_one(data, "./images/exit.xpm");
}

void	put_image(t_mlx_data *data, void *img, int y, int x)
{
	mlx_put_image_to_window(data->mlx, data->win, img, y, x);
}

// Function to display the map
void	draw_map(char **map, t_mlx_data d)
{
	int	x;
	int	y;
	int	sz;

	sz = 64;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '1')
				put_image(&d, d.wall, x * sz, y * sz);
			else if (map[y][x] == '0')
				put_image(&d, d.floor, x * sz, y * sz);
			else if (map[y][x] == 'P')
				put_image(&d, d.player, x * sz, y * sz);
			// else if (map[y][x] == 'C')
			//	put_image(&d, d.ice_cr, x * sz, y * sz);
			//else if (map[y][x] == 'E')
			//	put_image(&d, d.exit, x * sz, y * sz);
			x++;
		}
		y++;
	}
} */

void	free_map(char **map)
{
	int	i;

	i = -1;
	if (map)
	{
		while (map[++i])
			free(map[i]);
		free(map);
	}
}

int	main(int argc, char **argv)
{
	char		**map;

	(void )argc;

	map = handle_map(argv[1]);
	/*data.size = size;
	data.map = map;
	data.prev_is_exit = 0;
	data.n_of_moves = 0;
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	data.win = mlx_new_window(data.mlx, size.x * 64, size.y * 64, "game");
	if (data.win == NULL)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}
	load_images(&data);
	draw_map(map, data);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_key_hook(data.win, handle_input, &data);
	mlx_loop(data.mlx);*/
	return (0);
}
