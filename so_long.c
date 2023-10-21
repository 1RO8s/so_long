/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/21 10:49:30 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_images(t_game *g, int *width, int *height)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	g->images = images;
	images->img_wall = read_img(g, "./images/so_wall.xpm", width, height);
	images->img_item = read_img(g, "./images/so_item.xpm", width, height);
	images->img_player = read_img(g, "./images/so_player3.xpm", width, height);
	images->img_exit = read_img(g, "./images/so_exit.xpm", width, height);
	images->img_space[0] = read_img(g, "./images/space01.xpm", width, height);
}

void	game_setting(t_game *game)
{
	int	img_width;
	int	img_height;

	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, TILE_SIZE * game->width, TILE_SIZE
			* game->height, "so_long");
	read_images(game, &img_width, &img_height);
	game->move_count = 0;
	game->completed = FALSE;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->width = 0;
	game->height = 0;
	game->images = NULL;
	game->player = NULL;
	game->exit = NULL;
	game->map = NULL;
	game->item_count = 0;
	game->move_count = 0;
	game->errno = 0;
	game->completed = 0;
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	char	*map;

	if (arg_check(argc, argv))
		return (0);
	map = read_mapfile(argv[1]);
	if (map == NULL && ft_printf("Error\nファイルが空です\n"))
		exit(EXIT_FAILURE);
	game = malloc(sizeof(t_game));
	init_game(game);
	game->map = map;
	if (is_invalid_map(game))
	{
		print_errmsg(game);
		exit(EXIT_FAILURE);
	}
	game_setting(game);
	render(game);
	mlx_hook(game->window, 3, 1L << 1, press_keys, game);
	mlx_hook(game->window, 17, 0, destroy_window, game);
	mlx_hook(game->window, 19, 1L << 17, render, game);
	mlx_loop(game->mlx);
}
