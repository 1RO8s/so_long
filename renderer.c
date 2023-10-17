/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/17 15:18:32 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, void *img_ptr, int x, int y)
{
	mlx_put_image_to_window(
		game->mlx,
		game->window,
		img_ptr,
		TILE_SIZE * x,
		TILE_SIZE * y);
}

void	render_map(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g->map[(g->width + 1) * j + i] != '\0')
	{
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
			put_image(g, g->images->img_space[0], i, j);
		i++;
	}
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

int	render(t_game *game)
{
	render_map(game);
	render_player(game);
	return (0);
}
