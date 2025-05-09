/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:45:58 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/09 19:08:01 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

/* typedef struct s_point
{
	int	x;
	int	y;
}	t_x_and_y;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	void		*wall;
	void		*floor;
	void		*player;
	void		*play_u;
	void		*play_l;
	void		*play_r;
	void		*ice_cr;
	void		*exit;
	int			n_of_collectibles;
	t_x_and_y	size;
	t_x_and_y	ps;
	char		**map;
	int			prev_is_exit;
	int			n_of_moves;
}			t_mlx_data; */

int		ft_strlen_m(const char *s);
void	error(char *s, char **map, char *map_line);

//void	fill(char **tab, t_x_and_y size, t_x_and_y current, char *target);
bool	is_target(char c, char *target);
//void	find_start(char **map, t_x_and_y *start);
//void	check_map_is_playable(char **map2, char *map_line, char **map1);
//void	check_is_playable(char *map_l, t_x_and_y *sz, t_mlx_data *d, char **m1);

void	check_characters_array(int *characters_arr, char *map_line);
void	check_all_characters_are_present(char *map_line);
void	check_border_is_all_wall(char **map, char *map_line);

void	check_ber(char *s);
char	*create_map_line(int fd);
char	**create_map(char *map_line);
char	**handle_map(char *s);

/* int		close_game(t_mlx_data *data); */
void	free_map(char **map);
/* void	cleanup_map_and_textures(t_mlx_data *data);
void	clean_init_and_window(t_mlx_data *data); */
/*
void	print_moves(t_mlx_data *data);

void	move_player_up(t_mlx_data *data);
void	move_player_down(t_mlx_data *data);
void	move_player_left(t_mlx_data *data);
void	move_player_right(t_mlx_data *data);
int		handle_input(int keysym, t_mlx_data *data);

void	put_image(t_mlx_data *data, void *img, int y, int x);

void	load_images(t_mlx_data *data);
void	*load_one(t_mlx_data *data, char *s); */
