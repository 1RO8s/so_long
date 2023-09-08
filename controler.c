/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/08/29 14:14:51 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
* 関数の概要説明
* @param[in] paramA 第一引数の説明
* @param[out] paramB 第一引数の説明
* @return int 戻り値の説明
*/
static void	get_item(t_game *game, int idx)
{
	printf("GET ITEM!\n");
	game->item_count--;
	game->map[idx] = '0';
}

static void	goal(t_game *game)
{
	printf("!!GAME SET!!\n");
}

static int	can_move(char c)
{
	if (c == '0' || c == 'C' || c == 'E')
		return (1);
	else
		return (0);
}

// (game->width + 1) * y + x: index of map string
void	move_player(t_game *game, int keycode)
{
	int	x;
	int	y;

	x = game->player->x;
	y = game->player->y;
	if (keycode == KEY_UP)
		y--;
	else if (keycode == KEY_DOWN)
		y++;
	else if (keycode == KEY_RIGHT)
		x++;
	else if (keycode == KEY_LEFT)
		x--;
	if (game->map[(game->width + 1) * y + x] == '1')
		printf(" hit a wall!!\n");
	else if (can_move(game->map[(game->width + 1) * y + x]))
	{
		game->player->x = x;
		game->player->y = y;
		if (game->map[(game->width + 1) * y + x] == 'C')
			get_item(game, (game->width + 1) * y + x);
		if (game->map[(game->width + 1) * y + x] == 'E'
			&& game->item_count == 0)
			goal(game);
	}
}
