/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/09/05 07:39:07 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_memories(t_game *game)
{
	free(game->player);
	free(game);
	return (0);
}

int	destroy_window(int keycode, t_game *game)
{
	printf("\n--- destory_window ---\n");
	mlx_destroy_window(game->mlx, game->window);
	exit(0);
}

void	put_image(t_game *game, void *img_ptr, int x, int y)
{
	mlx_put_image_to_window(
		game->mlx,
		game->window,
		img_ptr,
		TILE_SIZE * x,
		TILE_SIZE * y);
}

// void render_space(t_game *g,int i,int j){

// 	g->height

// }

void	render_map(t_game *g)
{
	int	i;
	int	j;

	printf("\n--- render_map ---\n");
	i = 0;
	j = 0;
	while (g->map[(g->width + 1) * j + i] != '\0')
	{
		test_render_map(g, i, j);
		if (g->map[(g->width + 1) * j + i] == '\n')
		{
			i = 0;
			j++;
			continue ;
		}
		if (g->map[(g->width + 1) * j + i] == '1')
			put_image(g, g->images->img_wall, i, j);
		else if (g->map[(g->width + 1) * j + i] == 'C')
			put_image(g, g->images->img_item, i, j);
		else if (g->map[(g->width + 1) * j + i] == 'E')
			put_image(g, g->images->img_exit, i, j);
		if (g->map[(g->width + 1) * j + i] == '0')
			put_image(g, g->images->img_space[3], i, j);
		i++;
	}
	printf("\n");
}

void	render_player(t_game *game)
{
	mlx_put_image_to_window(
		game->mlx,
		game->window,
		game->images->img_player,
		TILE_SIZE * game->player->x,
		TILE_SIZE * game->player->y);
}

int	press_keys(int keycode, t_game *game)
{
	printf("\n--- press_keys %d ---\n", keycode);
	if (keycode == KEY_ESC)
		destroy_window(keycode, game);
	else if (
		keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_RIGHT
			|| keycode == KEY_LEFT)
	{
		move_player(game, keycode);
	}
	render_map(game);
	render_player(game);
	return (0);
}

// *mapからプレイヤー位置を取得して、game->playerに設定する
void	map_init(t_game *game)
{
	printf("\n--- map_init ---\n");
	printf("init map:\n%s\n", game->map);
}

char	*read_mapfile(void)
{
	char	*map;

	printf("\n--- read_mapfile ---\n");
	map = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (map == NULL)
	{
		// メモリ割り当てエラーの処理
		return (NULL);
	}
	strcpy(map,
			"1111111111\n"
			"1P00000CC1\n"
			"1001CC1CC1\n"
			"1CC1CC1001\n"
			"1CC00000E1\n"
			"1111111111");
	return (map);
}

// TODO: mapを読み取ってプレイヤー位置を取得
// プレイヤーは下向き開始
// プレイヤー位置のPを0に置き換える
void	read_player_position(t_game *game)
{
	t_position	*player;
	int			idx;

	player = malloc(sizeof(t_position));
	player->x = 1;
	player->y = 1;
	player->direction = KEY_DOWN;
	game->player = player;
	idx = (game->width + 1) * player->y + player->x;
	game->map[idx] = '0';
}

void	read_space_images(t_game *game, int *width, int *height)
{
	printf("\n--- read_space_images ---\n");
	game->images->img_space[0] = mlx_xpm_file_to_image(game->mlx,
														"./images/space01.xpm",
														width,
														height);
	game->images->img_space[1] = mlx_xpm_file_to_image(game->mlx,
														"./images/space02.xpm",
														width,
														height);
	game->images->img_space[2] = mlx_xpm_file_to_image(game->mlx,
														"./images/space03.xpm",
														width,
														height);
	game->images->img_space[3] = mlx_xpm_file_to_image(game->mlx,
														"./images/space04.xpm",
														width,
														height);
}

void	read_images(t_game *game, int *width, int *height)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	game->images = images;
	printf("\n--- read_images ---\n");
	images->img_wall = mlx_xpm_file_to_image(game->mlx, "./images/so_wall.xpm",
			width, height);
	printf("\n--- read space ---\n");
	read_space_images(game, width, height);
	// images->img_space[0] = mlx_xpm_file_to_image(game->mlx,
	// "./images/so_wall.xpm",
	// 		width, height);
	images->img_item = mlx_xpm_file_to_image(game->mlx, "./images/so_item.xpm",
			width, height);
	images->img_player = mlx_xpm_file_to_image(game->mlx,
												"./images/so_player3.xpm",
												width,
												height);
	images->img_exit = mlx_xpm_file_to_image(game->mlx, "./images/so_exit.xpm",
			width, height);
}

void	read_exit_position(t_game *game)
{
	t_position	*exit;

	exit = malloc(sizeof(t_position));
	exit->x = 3;
	exit->y = 8;
	game->exit = exit;
}

t_game	*game_setting(t_game *map_info)
{
	t_game		*g;
	t_position	*p;
	int			img_width;
	int			img_height;

	printf("\n--- game_setting ---\n");
	g = malloc(sizeof(t_game));
	g->map = map_info->map;
	g->width = map_info->width;
	g->height = map_info->height;
	g->item_count = map_info->item_count;
	g->mlx = mlx_init();
	g->window = mlx_new_window(g->mlx, TILE_SIZE * g->width, TILE_SIZE
			* g->height, "so_long");
	read_player_position(g);
	read_exit_position(g);
	read_images(g, &img_width, &img_height);
	return (g);
}

t_game	*get_map_info(char *map)
{
	t_game	*map_info;
	char	*c;

	printf("\n--- get_map_info ---\n");
	map_info = malloc(sizeof(t_game));
	map_info->map = map;
	c = map;
	while (*c != '\n')
	{
		map_info->width++;
		c++;
	}
	c = map;
	map_info->height++;
	while (*c != '\0')
	{
		if (*c == 'C')
			map_info->item_count++;
		if (*c == '\n')
			map_info->height++;
		c++;
	}
	return (map_info);
}


// deep first search
int	dfs(char *map, int x, int y)
{
	int	width;
	int	height;

	width = 10;
	height = 6;
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return (0); // マップの外に出たら経路なし
	}
	if (map[(width + 1) * y + x] == '1')
	{
		return (0); // 壁に当たったら経路なし
	}
	if (map[(width + 1) * y + x] == 'E')
	{
		return (1); // 出口に到達したら経路あり
	}
	map[(width + 1) * y + x] = '1'; // 訪れた場所を壁に変更
	// 上下左右に移動して探索
	if (dfs(map, x - 1, y) || dfs(map, x + 1, y) || dfs(map, x, y - 1)
		|| dfs(map, x, y + 1))
	{
		return (1);
	}
	map[(width + 1) * y + x] = '0'; // 訪れた場所を通路に戻す
	return (0);
}

int	map_validate(char *map)
{
	char	*c;
	int		item_count;
	int		exit_count;
	int		player_count;
	int		width;
	int		temp_width;

	printf("\n--- get_map_info ---\n");
	while (*c != '\0')
	{
		if (*c == 'C')
			item_count++;
		if (*c == 'E')
			exit_count++;
		if (*c == 'P')
			player_count++;
		if (*c == '\n')
		{
			width = 0;
		}
		width++;
		c++;
	}
	// 長方形になっているか確認
	// プレイヤーの初期位置が設定されていること
	// 出口が１つだけ設定されていること
	// アイテムが最低1つ設定されていること
	// 壁に囲われているか確認
	// 有効なパスがあるか確認
	return (1);
}

// int	main(void)
// {
// 	t_game	*g;
// 	t_game	*map_info;
// 	int		width;
// 	int		item_count;
// 	int		img_width;
// 	int		img_height;
// 	char	*map;

// 	// TODO マップファイルの読み込み
// 	map = read_mapfile();
// 	printf("%s\n", map);
// 	// TODO 正しいマップであることを確認
// 	map_info = get_map_info(map);
// 	printf("width:%d height:%d items:%d\n", map_info->width, map_info->height,
// 			map_info->item_count);
// 	// 初期設定
// 	g = game_setting(map_info);
// 	// マップ表示
// 	render_map(g);
// 	render_player(g);
// 	// フックの登録
// 	// mlx_key_hook(vars.window, press_keys, &vars);
// 	mlx_hook(g->window, 3, 1L << 1, press_keys, g);
// 	// mlx_hook(game.window,2,1L<<0,close_win,&game);
// 	printf("\nset  hooks\n");
// 	mlx_loop(g->mlx);
// }

int	main(void)
{
	char	*map;

	map = read_mapfile();
	printf("%s\n", map);
	if (dfs(map, 1, 1))
	{
		printf("プレイヤーから出口への経路が存在します\n");
	}
	else
	{
		printf("プレイヤーから出口への経路は存在しません\n");
	}
}
