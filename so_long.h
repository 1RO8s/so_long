/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 07:59:50 by hnagasak          #+#    #+#             */
/*   Updated: 2023/09/03 03:34:51 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// # include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

# define BUFFER_SIZE 1000
# define TILE_SIZE 32

typedef struct s_position
{
	int			x;
	int			y;
	int			direction;
}				t_position;

typedef struct s_images
{
	void		*img_wall;
	void		*img_space[10];
	void		*img_item;
	void		*img_player;
	void		*img_exit;
}				t_images;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_images *images;
	// void		*img_wall;
	// void		*img_space;
	// void		*img_item;
	// void		*img_player;
	// void		*img_exit;
	t_position	*player;
	t_position	*exit;
	char		*map;
	int			item_count;
}				t_game;

void	move_player(t_game *game, int keycode);

// for debug
void	show_stat(t_game *g, int num);
void	test_render_map(t_game *g, int i, int j);

#endif
