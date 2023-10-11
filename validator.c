/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/11 09:27:21 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * If g->map is a rectangle, return 1 and set its height and width.
 * @param[in]	g	t_game to be verified
 */
int	is_rectangle(t_game *g)
{
	char	*c;
	int		width;
	int		temp_width;

	c = g->map;
	width = 0;
	temp_width = 0;
	g->height = 1;
	while (*c != '\0')
	{
		if (*c == '\n')
		{
			if (temp_width == 0)
				temp_width = width;
			else if (temp_width != width)
				return (FALSE);
			width = 0;
			g->height++;
		}
		else
			width++;
		c++;
	}
	g->width = width;
	return (TRUE);
}

int	is_walled_in(t_game *g)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (g->map[(g->width + 1) * y + x] != '\0')
	{
		if (g->map[(g->width + 1) * y + x] == '\n')
		{
			x = 0;
			y++;
			continue ;
		}
		if (x == 0 || x == g->width - 1 || y == 0 || y == g->height - 1)
		{
			if (g->map[(g->width + 1) * y + x] != '1')
				return (FALSE);
		}
		x++;
	}
	return (TRUE);
}

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

t_position	*cps(int x, int y)
{
	t_position	*pos;

	pos = malloc(sizeof(t_position));
	pos->x = x;
	pos->y = y;
	return (pos);
}

// deep first search
int	dfs(t_game *g, char *_map, t_position *_p)
{
	int			width;
	char		*map;
	t_position	*p;

	map = ft_strdup(_map);
	p = _p;
	width = g->width;
	if (map[(width + 1) * p->y + p->x] == '1')
		return (0);
	if (map[(width + 1) * p->y + p->x] == 'E')
		return (1);
	map[(width + 1) * p->y + p->x] = '1';
	if (dfs(g, map, cps(p->x - 1, p->y)) || dfs(g, map, cps(p->x + 1, p->y))
		|| dfs(g, map, cps(p->x, p->y - 1)) || dfs(g, map, cps(p->x, p->y + 1)))
	{
		return (1);
	}
	map[(width + 1) * p->y + p->x] = '0';
	free(map);
	map = NULL;
	return (0);
}

/**
 * Set player position and direction.
 * @param[in]  g  t_game to set exit 
 * @param[in]  _map map to be verified
 * @param[in]  _p potision to be verified
 * @param[in]  direction direction of player
 */
int	alitem(t_game *g, char *_map, t_position *_p, int item_count)
{
	int			width;
	char		*map;
	t_position	*p;

	map = ft_strdup(_map);
	p = _p;
	width = g->width;
	if (map[(width + 1) * p->y + p->x] == 'C' && ++item_count == g->item_count)
		return (1);
	if (map[(width + 1) * p->y + p->x] == '1')
		return (0);
	map[(width + 1) * p->y + p->x] = '1';
	if (alitem(g, map, cps(p->x - 1, p->y), item_count) || alitem(g, map,
			cps(p->x + 1, p->y), item_count) || alitem(g, map, cps(p->x, p->y
				- 1), item_count) || alitem(g, map, cps(p->x, p->y + 1),
			item_count))
	{
		return (1);
	}
	map[(width + 1) * p->y + p->x] = '0';
	free(map);
	map = NULL;
	return (0);
}

/**
 * Returns 1 if it is a invalid map
 * @param[in]  g  t_game with map to be verified
 */
int	is_invalid_map(t_game *g)
{
	printf("\n--- is_invalid_map ---\n");
	if (!is_rectangle(g))
	{
		g->errno = NOT_RECTANGLE;
		return (TRUE);
	}
	if (!is_walled_in(g))
	{
		g->errno = NOT_WALLED;
		return (TRUE);
	}
	if (!has_required_elements(g))
		return (TRUE);
	if (!dfs(g, g->map, g->player))
	{
		g->errno = UNREACHABLE_EXIT;
		return (TRUE);
	}
	if (!alitem(g, g->map, g->player, 0))
	{
		g->errno = UNCOLLECTIBLE_ITEM;
		return (TRUE);
	}
	return (FALSE);
}
