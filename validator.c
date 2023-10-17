/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/17 19:06:16 by hnagasak         ###   ########.fr       */
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
	int		tmp_width;

	c = g->map;
	tmp_width = 0;
	g->height = 1;
	while (*c != '\0')
	{
		if (*c != '\n')
			tmp_width++;
		else
		{
			if (g->width == 0)
				g->width = tmp_width;
			else if (g->width != tmp_width)
				return (FALSE);
			tmp_width = 0;
			g->height++;
		}
		c++;
	}
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
 * If all items are collectible, return (1); 
 * @param[in]  g  t_game to set items 
 * @param[in]  _map map to be verified
 * @param[in]  _p potision to be verified
 * @param[in]  item_count number of collectible items
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
