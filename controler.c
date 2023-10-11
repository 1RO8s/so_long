/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/11 09:48:25 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

/**
* Decrease item_count, and change the character at the current position to 0
* @param[in] game target t_game
* @param[out] idx index indicating how many characters of map
* @return void 
*/
static void	get_item(t_game *game, int idx)
{
	game->item_count--;
	game->map[idx] = '0';
}

static void	goal(t_game *game)
{
	ft_printf("!!STAGE CLEAR!!\n");
	game->completed = TRUE;
}

static int	can_move(char c)
{
	if (c == '0' || c == 'C' || c == 'E')
		return (1);
	else
		return (0);
}

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
	if (can_move(game->map[(game->width + 1) * y + x]))
	{
		game->player->x = x;
		game->player->y = y;
		if (game->map[(game->width + 1) * y + x] == 'C')
			get_item(game, (game->width + 1) * y + x);
		if (game->map[(game->width + 1) * y + x] == 'E'
			&& game->item_count == 0)
			goal(game);
		game->move_count++;
	}
	ft_printf("移動回数:%d\n", game->move_count);
}
