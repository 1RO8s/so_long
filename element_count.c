/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/11 09:49:58 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Set player position and direction.
 * @param[in]  game  t_game to set exit 
 * @param[in]  x X coordinate of player
 * @param[in]  y Y coordinate of player
 * @param[in]  direction direction of player
 */
int	set_player_position(t_game *game, int x, int y, int direction)
{
	t_position	*player;
	int			idx;

	player = malloc(sizeof(t_position));
	player->x = x;
	player->y = y;
	player->direction = direction;
	game->player = player;
	idx = (game->width + 1) * player->y + player->x;
	game->map[idx] = '0';
	return (1);
}

/**
 * Set exit position.
 * @param[in]  game  t_game to set exit 
 * @param[in]  x X coordinate of Exit
 * @param[in]  y Y coordinate of Exit
 */
int	set_exit_position(t_game *game, int x, int y)
{
	t_position	*exit;

	exit = malloc(sizeof(t_position));
	exit->x = x;
	exit->y = y;
	game->exit = exit;
	return (1);
}

int	set_item_count(t_game *g, int item_count)
{
	g->item_count = item_count;
	return (item_count);
}

void	count_required_element(t_game *g, t_count *count)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ft_memset(count, 0, sizeof(t_count));
	while (g->map[(g->width + 1) * y + x] != '\0')
	{
		if (g->map[(g->width + 1) * y + x] == '\n')
		{
			x = 0;
			y++;
			continue ;
		}
		if (g->map[(g->width + 1) * y + x] == 'C')
			count->item = set_item_count(g, ++count->item);
		if (g->map[(g->width + 1) * y + x] == 'E')
			count->exit += set_exit_position(g, x, y);
		if (g->map[(g->width + 1) * y + x] == 'P')
			count->player += set_player_position(g, x, y, KEY_DOWN);
		x++;
	}
}

int	has_required_elements(t_game *g)
{
	t_count	count;

	count_required_element(g, &count);
	if (count.player != 1)
		g->errno = NO_PLAYER_POSITION;
	if (count.exit != 1)
		g->errno = NO_EXIT_POSITION;
	if (count.item < 1)
		g->errno = NO_ITEMS;
	if (g->errno != 0)
		return (FALSE);
	return (TRUE);
}
