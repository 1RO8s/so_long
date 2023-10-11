/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/11 09:28:37 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	destroy_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	free(game->player);
	free(game->exit);
	if (game->images != NULL)
	{
		free(game->images->img_exit);
		free(game->images->img_item);
		free(game->images->img_player);
		free(game->images->img_wall);
		free(game->images->img_space[0]);
	}
	free(game->images);
	free(game->map);
	game->player = NULL;
	game->exit = NULL;
	game->images = NULL;
	game->map = NULL;
	free(game);
	exit(0);
}

int	press_keys(int kcd, t_game *game)
{
	if (kcd == KEY_ESC)
		destroy_window(game);
	if (game->completed)
		return (0);
	else if (
		kcd == KEY_UP || kcd == KEY_DOWN || kcd == KEY_RIGHT || kcd == KEY_LEFT)
	{
		move_player(game, kcd);
		render_map(game);
		render_player(game);
	}
	return (0);
}

char	*read_mapfile(char *file_name)
{
	int		fd;
	char	*line;
	char	*old_map;
	char	*map;

	old_map = NULL;
	map = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		perror("ファイルを開けませんでした");
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map = ft_strjoin(old_map, line);
		if (old_map != NULL)
			free(old_map);
		old_map = ft_strdup(map);
	}
	close(fd);
	return (map);
}

void	*read_img(t_game *g, char *file, int *width, int *height)
{
	return (mlx_xpm_file_to_image(g->mlx, file, width, height));
}

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

void	print_errmsg(int errno)
{
	if (errno == NO_PLAYER_POSITION)
		ft_printf("プレイヤーの初期位置を設定してください\n");
	if (errno == NO_EXIT_POSITION)
		ft_printf("出口を設定してください\n");
	if (errno == NO_ITEMS)
		ft_printf("アイテムを1つ以上設定してください\n");
	if (errno == NOT_RECTANGLE)
		ft_printf("長方形のマップを使用してください\n");
	if (errno == NOT_WALLED)
		ft_printf("壁に囲まれたマップを使用してください\n");
	if (errno == UNREACHABLE_EXIT)
		ft_printf("出口に到達出来ないマップです\n");
	if (errno == UNCOLLECTIBLE_ITEM)
		ft_printf("アイテムが回収できないマップです\n");
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	char	*map;

	if (argc != 2)
		return (0);
	map = read_mapfile(argv[1]);
	if (map == NULL)
		exit(EXIT_FAILURE);
	game = malloc(sizeof(t_game));
	game->map = map;
	game->errno = 0;
	if (is_invalid_map(game))
	{
		print_errmsg(game->errno);
		exit(EXIT_FAILURE);
	}
	game_setting(game);
	render_map(game);
	render_player(game);
	mlx_hook(game->window, 3, 1L << 1, press_keys, game);
	mlx_hook(game->window, 17, 0, destroy_window, game);
	mlx_loop(game->mlx);
}
