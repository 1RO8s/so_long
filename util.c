/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/11 09:52:22 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_position	*cps(int x, int y)
{
	t_position	*pos;

	pos = malloc(sizeof(t_position));
	pos->x = x;
	pos->y = y;
	return (pos);
}

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
