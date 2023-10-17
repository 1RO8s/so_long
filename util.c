/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/17 18:54:48 by hnagasak         ###   ########.fr       */
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

void	*read_img(t_game *g, char *file, int *width, int *height)
{
	return (mlx_xpm_file_to_image(g->mlx, file, width, height));
}

int	destroy_window(t_game *game)
{
	if (game->mlx != NULL)
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

void	print_errmsg(t_game *game)
{
	int	errno;

	errno = game->errno;
	if (errno == NOT_RECTANGLE)
		ft_printf("Error\n長方形のマップを使用してください\n");
	if (errno == NOT_WALLED)
		ft_printf("Error\n壁に囲まれたマップを使用してください\n");
	if (errno == INVALID_ELEMENT)
		ft_printf("Error\n0,1,C,E,P以外の文字を含めないでください\n");
	if (errno == NO_PLAYER_POSITION)
		ft_printf("Error\nプレイヤーを1つだけ設定してください\n");
	if (errno == NO_EXIT_POSITION)
		ft_printf("Error\n出口を1つだけ設定してください\n");
	if (errno == NO_ITEMS)
		ft_printf("Error\nアイテムを1つ以上設定してください\n");
	if (errno == UNREACHABLE_EXIT)
		ft_printf("Error\n出口に到達出来ないマップです\n");
	if (errno == UNCOLLECTIBLE_ITEM)
		ft_printf("Error\nアイテムが回収できないマップです\n");
	destroy_window(game);
}

int	is_invalid_element(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'E' || c == 'C')
		return (FALSE);
	else
		return (TRUE);
}
